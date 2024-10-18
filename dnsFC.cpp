#include <iostream>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT1 5050 // Port for server1
#define PORT2 6060 // Port for server2

using namespace std;

int main() {
    int client_fd1, client_fd2;
    struct sockaddr_in server1_address, server2_address;
    char buffer[1024] = {0};

    // Create socket for server 1
    if ((client_fd1 = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error for Server 1");
        return -1;
    }

    // Server 1 address setup
    server1_address.sin_family = AF_INET;
    server1_address.sin_port = htons(PORT1);

    if (inet_pton(AF_INET, "127.0.0.1", &server1_address.sin_addr) <= 0) {
        cout << "Invalid address for Server 1" << endl;
        return -1;
    }

    // Create socket for server 2
    if ((client_fd2 = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error for Server 2");
        return -1;
    }

    // Server 2 address setup
    server2_address.sin_family = AF_INET;
    server2_address.sin_port = htons(PORT2);

    if (inet_pton(AF_INET, "127.0.0.1", &server2_address.sin_addr) <= 0) {
        cout << "Invalid address for Server 2" << endl;
        return -1;
    }

    while (true) {
        string hostname;
        cout << "Enter hostname to resolve (or type 'exit' to quit): ";
        cin >> hostname;

        if (hostname == "exit") {
            break;
        }

        // Connect to server 1
        if (connect(client_fd1, (struct sockaddr *)&server1_address, sizeof(server1_address)) >= 0) {
            send(client_fd1, hostname.c_str(), hostname.length(), 0);
            memset(buffer, 0, sizeof(buffer));
            int valread = read(client_fd1, buffer, 1024);

            if (valread > 0) {
                cout << "Server 1 Resolved IP: " << buffer << endl;
            } else {
                // Try server 2 if not found in server 1
                if (connect(client_fd2, (struct sockaddr *)&server2_address, sizeof(server2_address)) >= 0) {
                    send(client_fd2, hostname.c_str(), hostname.length(), 0);
                    memset(buffer, 0, sizeof(buffer));
                    valread = read(client_fd2, buffer, 1024);

                    if (valread > 0) {
                        cout << "Server 2 Resolved IP: " << buffer << endl;
                    } else {
                        cout << "Hostname not found in both servers" << endl;
                    }
                }
            }
        }

        // Close both sockets after use
        close(client_fd1);
        close(client_fd2);
    }

    return 0;
}
