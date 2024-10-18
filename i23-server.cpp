#include<bits/stdc++.h>                                                                                                                                                
#include <iostream>                                                                                                                                                    
#include <cstring>                                                                                                                                                     
#include <sys/socket.h>                                                                                                                                                
#include <netinet/in.h>                                                                                                                                                
#include <unistd.h>                                                                                                                                                    
#include <arpa/inet.h>                                                                                                                                                 
#define PORT 6062                                                                                                                                                      
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
                                                                                                                                                                       
    //        send(client_socket, data, strlen(data), 0);                                                                                                              
                                                                                                                                                                       
    read(client_socket, buffer, 1024);                                                                                                                                 
    int x1=atoi(buffer)*atoi(buffer);                                                                                                                                  
    int x2=x1*atoi(buffer);                                                                                                                                            
    cout<<x1<<" "<<x2;                                                                                                                                                 
    char buff1[10],buff2[10];                                                                                                                                          
    int i=0;                                                                                                                                                           
    for(auto c:to_string(x1)){                                                                                                                                         
            buff1[i++]=c;                                                                                                                                              
    }                                                                                                                                                                  
    i=0;                                                                                                                                                               
    for(auto c:to_string(x2)){                                                                                                                                         
        buff2[i++]=c;                                                                                                                                                  
    }                                                                                                                                                                  
    send(client_socket,buff1,to_string(x1).length(),0);                                                                                                                
    send(client_socket,buff2,to_string(x2).length(),0);                                                                                                                
    close(client_socket);                                                                                                                                              
    close(server_fd);                                                                                                                                                  
    return 0;                                                                                                                                                          
} 
