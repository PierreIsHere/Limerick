#include"libs.h"

int clientLimit;

void * clientThread(void *arg)
{
    char client_message[2000];
    int clientSocket = *((int *)arg);
    recv(clientSocket , client_message , 2000 , 0);
    printf("Received - %s - %d",client_message,clientSocket);
    send(clientSocket,"Test",6,0);
    printf("Exit socketThread \n");
    close(clientSocket);
    pthread_exit(NULL);
}
int connect(){
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;
    //Creating the host socket 
    serverSocket = socket(PF_INET, SOCK_STREAM, 0);
    // Configuring family, port and address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7799);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //Convention of padding the socket structure
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
    //Combining socket with supplied information
    bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

    //Setting the socket to listen with a clientLimit amount of connections qeued 
    if(listen(serverSocket,clientLimit)==0)printf("Listening\n");
    else printf("Error\n");
    //Instantiating an array of thread identifiers
    pthread_t threadID[clientLimit];
    int i = 0;
    for(;;){
        //Accept call creates a new socket for the incoming connection
        addr_size = sizeof serverStorage;
        clientSocket = accept(serverSocket, (struct sockaddr *) &serverStorage, &addr_size);
        //for each client request creates a thread and assign the client request to it to process
        //so the main thread can entertain next request
        if( pthread_create(&threadID[i], NULL, clientThread, &clientSocket) != 0 )
            printf("Failed to create thread\n");
        if( i >= clientLimit)
        {
            i = 0;
            while(i < clientLimit)
            {
            pthread_join(threadID[i++],NULL);
            }
            i = 0;
        }
    }
  return 1;
}