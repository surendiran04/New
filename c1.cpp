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

    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        cout << "Invalid address/Address not supported" << endl;
        return -1;
    }

    if (connect(client_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        cout << "Connection Failed" << endl;
        return -1;
    }

    while (true) {
        string message;
        cout << "Enter a message (type 'bye' to exit): ";
        getline(cin, message);

        send(client_fd, message.c_str(), message.length(), 0);
        if (message == "bye") {
            break;
        }
        memset(buffer, 0, sizeof(buffer));
        int valread = read(client_fd, buffer, 1024);

        if (valread > 0) {
            cout << "Received: " << buffer << endl;

            if (strcmp(buffer, "bye") == 0) {
                break;
            }
        }
    }

    // Close the socket
    close(client_fd);
    return 0;
}
