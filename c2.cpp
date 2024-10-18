#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

#define PORT 5050

using namespace std;

int main() {
    int client_fd;
    struct sockaddr_in server_address;
    char buffer[1024] = {0};

    // Create socket
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    // Convert IPv4 address from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        cout << "Invalid address/Address not supported" << endl;
        return -1;
    }

    // Connect to the server
    if (connect(client_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        cout << "Connection Failed" << endl;
        return -1;
    }

    while (true) {
        // Receive message from the server first
        memset(buffer, 0, sizeof(buffer));
        int valread = read(client_fd, buffer, 1024);

        if (valread > 0) {
            cout << "Received: " << buffer << endl;

            // If "bye" is received, exit the loop
            if (strcmp(buffer, "bye") == 0) {
                break;
            }

            // Now send a reply to the server
            string reply;
            cout << "Enter a reply message (type 'bye' to exit): ";
            getline(cin, reply);

            send(client_fd, reply.c_str(), reply.length(), 0);

            if (reply == "bye") {
                break;
            }
        }
    }

    // Close the socket
    close(client_fd);
    return 0;
}
