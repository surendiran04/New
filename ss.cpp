#include<bits/stdc++.h>                                                                                                                                                
#include <sys/socket.h>                                                                                                                                                
#include <netinet/in.h>                                                                                                                                                
#include <unistd.h>                                                                                                                                                    
#include <arpa/inet.h>                                                                                                                                                 
#define PORT 5050                                                                                                                                                      
using namespace std;                                                                                                                                                   
int main() {                                                                                                                                                           
        int server_fd, client_socket;                                                                                                                                  
        struct sockaddr_in address;                                                                                                                                    
        int addrlen = sizeof(address);                                                                                                                                 
        char buffer[1024] = {0};                                                                                                                                       
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {                                                                                                      
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
        }                                                                                                                                                              
        cout << "Server listening on port " << PORT << endl;                                                                                                           
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {                                                             
                perror("Accept failed");                                                                                                                               
                exit(EXIT_FAILURE);                                                                                                                                    

        }                                                                                                                                                              
        //read(client_socket, buffer, 1024);                                                                                                                           
        int x;                                                                                                                                                         
        read(client_socket, &x,4);                                                                                                                                     
        cout<<x;                                                                                                                                                       
        close(client_socket);                                                                                                                                          
        close(server_fd);                                                                                                                                              
        return 0;                                                                                                                                                      
} 
