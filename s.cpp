#include <iostream>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

#define PORT 5050
#define MAX_CLIENTS 2

using namespace std;

int client_sockets[MAX_CLIENTS];  

void handle_client(int client_socket, int other_client_socket) {
    char buffer[1024];
    
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int valread = read(client_socket, buffer, 1024);
        
        if (valread > 0) {
            cout << "Received from client: " << buffer << endl;

            // If message is "bye", end communication for both clients
            if (strcmp(buffer, "bye") == 0) {
                send(other_client_socket, buffer, strlen(buffer), 0);
                break;
            }

            // Forward the message to the other client
            send(other_client_socket, buffer, strlen(buffer), 0);
        }
    }

    close(client_socket);
}

int main() {
    int server_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Bind to the address and port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Start listening for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    cout << "Server listening on port " << PORT << endl;

    // Accept connections from two clients
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if ((client_sockets[i] = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }
        cout << "Client " << i + 1 << " connected." << endl;
    }

    // Create two threads to handle each client
    thread t1(handle_client, client_sockets[0], client_sockets[1]);
    thread t2(handle_client, client_sockets[1], client_sockets[0]);
    t1.join();
    t2.join();
    close(server_fd);
    return 0;
}
