#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5050 // Port for mediator

using namespace std;

int main() {
    int client_fd;
    struct sockaddr_in mediator_address;
    char buffer[1024] = {0};

    // Create socket
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }

    mediator_address.sin_family = AF_INET;
    mediator_address.sin_port = htons(PORT);

    // Convert address to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &mediator_address.sin_addr) <= 0) {
        cout << "Invalid address for mediator" << endl;
        return -1;
    }

    // Connect to mediator
    if (connect(client_fd, (struct sockaddr *)&mediator_address, sizeof(mediator_address)) < 0) {
        cout << "Connection to mediator failed" << endl;
        return -1;
    }

    while (true) {
        string hostname;
        cout << "Enter hostname to resolve: ";
        cin >> hostname;

        // Send hostname to mediator
        send(client_fd, hostname.c_str(), hostname.length(), 0);

        // Receive response from mediator
        memset(buffer, 0, sizeof(buffer));
        int valread = read(client_fd, buffer, 1024);
        if (valread > 
