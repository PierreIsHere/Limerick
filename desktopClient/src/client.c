// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h>
#include <pthread.h>

#define PORT 8888 
void *input(void *sock);
void *output(void *sock);    

int main(int argc, char const *argv[]) 
{ 
    int sock = 0; 
    struct sockaddr_in serv_addr; 
    pthread_t inThread,outThread; 
    
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    }
    pthread_create(&inThread, NULL, input, (void *)&sock); 
    pthread_join(inThread, NULL);
    pthread_create(&outThread, NULL, output, (void *)&sock); 
    pthread_join(outThread, NULL); 
    return 0; 
}
void *input(void *sock){
    char inp[1024];
    for(;;){
    scanf("%s",&inp);
    inp[strlen(inp)]= '\0';
    printf("%d",write((long)sock , inp , 1024));
    }
    
}
void *output(void *sock){
    char buffer[1024];
    for(;;){
        if(read((long)sock,buffer,1024)>0){
            printf("%s",buffer);
        }
    }
}