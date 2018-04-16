#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 60000
  
int main(int argc, char const *argv[])
{
    int sock = 0, valread;
    struct sockaddr_in address;
    struct sockaddr_in serv_addr;
    char response[4];
    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        exit(1);
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        exit(1);
    }
    
    
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        exit(1);
    }
    while(1){
    
        //reads message from server
        valread = read( sock , buffer, 1024);
        printf("%s\n",buffer );
    
        scanf("%s", response);
    
    
        //sends message to server
        send(sock , response , strlen(response) , 0 );
    
    close(sock);
    
    }
}