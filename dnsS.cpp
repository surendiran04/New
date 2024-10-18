#include <iostream>
#include <string>
#include <cstring>
#include <unordered_map>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 6060 // Port for server

using namespace std;

int main() {
    int server_fd, mediator_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    unordered_map<string, string> dns_table = {
        {"example.com", "93.184.216.34"},
        {"google.com", "142.250.190.78"},
        {"openai.com", "104.18.13.148"}
    };

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

    // Listen for connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    cout << "DNS Server is listening on port " << PORT << endl;

    // Accept connection from mediator
    if ((mediator_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int valread = read(mediator_socket, buffer, 1024);
        if (valread > 0) {
            string hostname(buffer);
            cout << "Received request to resolve: " << hostname << endl;

            string response;
            if (dns_table.find(hostname) != dns_table.end()) {
                response = dns_table[hostname];
            } else {
                response = "IP not found";
            }

            send(mediator_socket, response.c_str(), response.length(), 0);
            cout << "Sent IP: " << response << endl;
        }
    }

    close(mediator_socket);
    close(server_fd);

    return 0;
}
