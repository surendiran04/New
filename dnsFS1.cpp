#include <iostream>
#include <cstring>
#include <string>
#include <unordered_map>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 5050 // Port for Server 1

using namespace std;

int main() {
    unordered_map<string, string> dns_table1 = {
        {"example.com", "192.168.1.1"},
        {"server1.com", "192.168.1.2"}
    };

    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    while (true) {
        client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (client_socket < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        memset(buffer, 0, sizeof(buffer));
        read(client_socket, buffer, 1024);

        string hostname(buffer);
        string ip_address = "Not found";

        if (dns_table1.find(hostname) != dns_table1.end()) {
            ip_address = dns_table1[hostname];
        }

        send(client_socket, ip_address.c_str(), ip_address.length(), 0);
        close(client_socket);
    }

    close(server_fd);
    return 0;
}
