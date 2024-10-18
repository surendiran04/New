#include <iostream>
#include <string>
#include <unordered_map>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5050 // Port for mediator

using namespace std;

int main() {
    int mediator_fd, client_socket, server_socket;
    struct sockaddr_in address, server_address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    unordered_map<string, string> cache = {{"microsoft.com","125.10.36.14"},{"annauniv.edu","119.168.1.200"}}; // Cache for storing resolved IPs

    // Create mediator socket
    if ((mediator_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind mediator socket
    if (bind(mediator_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for client connection
    if (listen(mediator_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    cout << "Mediator is listening on port " << PORT << endl;

    // Accept connection from client
    if ((client_socket = accept(mediator_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Client accept failed");
        exit(EXIT_FAILURE);
    }
    cout << "Client connected." << endl;

    // Setup connection to server
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(6060); // Port of the DNS Server

    // Convert address to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        cout << "Invalid address for server" << endl;
        return -1;
    }

    // Connect to DNS Server
    if (connect(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        cout << "Server connection failed" << endl;
        return -1;
    }

    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int valread = read(client_socket, buffer, 1024);
        if (valread > 0) {
            string hostname(buffer);
            cout << "Received request from client: " << hostname << endl;

            // Check if hostname exists in cache
            if (cache.find(hostname) != cache.end()) {
                string cached_ip = cache[hostname];
                cout << "Found in cache: " << cached_ip << endl;
                send(client_socket, cached_ip.c_str(), cached_ip.length(), 0);
            } else {
                // Forward request to DNS Server
                send(server_socket, hostname.c_str(), hostname.length(), 0);
                memset(buffer, 0, sizeof(buffer));
                read(server_socket, buffer, 1024);
                string ip(buffer);
                cout << "Received from DNS server: " << ip << endl;

                // Cache the IP address
                cache[hostname] = ip;

                // Send IP back to client
                send(client_socket, ip.c_str(), ip.length(), 0);
            }
        }
    }

    close(client_socket);
    close(server_socket);
    close(mediator_fd);

    return 0;
}
