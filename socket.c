#include <stdlib.h>
#include "socket.h"

int start(){
    /* Variablen für den Server */
    int sock;
    struct sockaddr_in server;
    struct sockaddr_in client;
    int fileDescriptor;

    printf("Starting cKey-Server...\n");



    /* Anlegen eines Sockets */
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("creating stream socket");
        exit(1);
    }
    printf("Socket created.\n");



    /* Binden eines Sockets */
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(1995);

    if(bind( sock, (struct sockaddr *) &server, sizeof(server))<0){
        perror("Error on binding");
    };
    /*printf("Socket binded.\n");*/

    //Shared Memory erstellen
    shmem();



    /* Auf Verbindung hören */
    if(listen(sock, 5)<0){
        perror("Error on listening");
    };
    /*printf("Listening...\n");*/



    /* Verbindung aktzeptieren */
    socklen_t client_len;
    client_len = sizeof(client);

    while(1) {
        fileDescriptor = accept(sock, (struct sockaddr *) &client, &client_len);
        printf("Connection!\n");
    }
    return 0;
}

