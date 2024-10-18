#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

#define PORT 5050

using namespace std;

int main() {
    int server_fd, client1_socket, client2_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Start listening for connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    cout << "Server listening on port " << PORT << endl;

    // Accept connection from Client 1
    if ((client1_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Client 1 accept failed");
        exit(EXIT_FAILURE);
    }
    cout << "Client 1 connected." << endl;

    // Accept connection from Client 2
    if ((client2_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Client 2 accept failed");
        exit(EXIT_FAILURE);
    }
    cout << "Client 2 connected." << endl;

    while (true) {
        // Receive message from Client 1
        memset(buffer, 0, sizeof(buffer));
        int valread = read(client1_socket, buffer, 1024);
        if (valread <= 0 || strcmp(buffer, "bye") == 0) {
            cout << "Client 1 disconnected." << endl;
            break;
        }
        cout << "Received from Client 1: " << buffer << endl;

        // Server decides whether to edit the message
        string message = buffer;
        string editedMessage;
        cout << "Do you want to edit the message before sending to Client 2? (yes/no): ";
        string choice;
        cin >> choice;
        if (choice == "yes") {
            cout << "Enter the edited message: ";
            cin.ignore();
            getline(cin, editedMessage);
        } else {
            editedMessage = message;
        }

        // Send message to Client 2
        send(client2_socket, editedMessage.c_str(), editedMessage.length(), 0);

        // Receive reply from Client 2
        memset(buffer, 0, sizeof(buffer));
        valread = read(client2_socket, buffer, 1024);
        if (valread <= 0 || strcmp(buffer, "bye") == 0) {
            cout << "Client 2 disconnected." << endl;
            break;
        }
        cout << "Received from Client 2: " << buffer << endl;

        // Server decides whether to edit the reply before sending to Client 1
        message = buffer;
        cout << "Do you want to edit the reply before sending to Client 1? (yes/no): ";
        cin >> choice;
        if (choice == "yes") {
            cout << "Enter the edited reply: ";
            cin.ignore();
            getline(cin, editedMessage);
        } else {
            editedMessage = message;
        }

        // Send reply to Client 1
        send(client1_socket, editedMessage.c_str(), editedMessage.length(), 0);
    }

    // Close the sockets
    close(client1_socket);
    close(client2_socket);
    close(server_fd);

    return 0;
}
