#include <iostream>                                                                                                                                                    
#include <cstring>                                                                                                                                                     
#include <sys/socket.h>                                                                                                                                                
#include <arpa/inet.h>                                                                                                                                                 
#include <unistd.h>                                                                                                                                                    
#include<bits/stdc++.h>                                                                                                                                                
#define PORT 6062                                                                                                                                                      
                                                                                                                                                                       
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
    int x;                                                                                                                                                             
    cout<<"Enter a number:";                                                                                                                                           
    cin>>x;                                                                                                                                                            
    char buff[10];                                                                                                                                                     
    string n=to_string(x);                                                                                                                                             
    int i=0;                                                                                                                                                           
    for(auto m:n){                                                                                                                                                     
            buff[i++]=m;                                                                                                                                               
    }                                                                                                                                                                  
    send(client_fd,buff,n.length(), 0);                                                                                                                                
    int valread = read(client_fd, buffer, 1024);                                                                                                                       
    if (valread > 0) {                                                                                                                                                 
            cout << "Received: " << buffer << endl;                                                                                                                    
    }                                                                                                                                                                  
    valread = read(client_fd, buffer, 1024);                                                                                                                           
    if (valread > 0) {                                                                                                                                                 
            cout << "Received: " << buffer << endl;                                                                                                                    
    }                                                                                                                                                                  
    close(client_fd);                                                                                                                                                  
    return 0;                                                                                                                                                          
} 
