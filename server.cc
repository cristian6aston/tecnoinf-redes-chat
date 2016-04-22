#include <iostream>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

//#define PORT 8090
#define BACKLOG 5 // Numero de Conexiones (Esto no deberia ser así)
#define MAXDATASIZE 5000

void processMessage(int fd) {
    printf("4");
    int n;
    char buffer[MAXDATASIZE];
    bzero(buffer,MAXDATASIZE);
    n = read(fd,buffer,MAXDATASIZE);
    if (n < 0) {
        printf("ERROR reading from socket\n");
        // return -1;
    }   
    printf("debug : se ha conectado : %s\n",buffer);
    std::string userName;
    userName=buffer;

    std::cout << "blablabla" << userName;
    n = write(fd,"I got your message",18);
    if (n < 0) {
        printf("debug : se ha conectado : %s\n",buffer);
    }
    else {
        if (n > 0) {

        }
    }
/*
Para crear un thread nos valdremos de la función 
pthread_create 
de la biblioteca y 
de  la  estructura  de  datos  pthread_t  que  identifica  cada  thread  diferenciándolo  de  los  
demás y que contiene todos sus datos.  
El prototipo de la función es el siguiente:  
i
nt  pthread_create(pthread_t  *  thread, pthread_attr_t *attr, 
void * (*start_routine)(void *), void *arg)  
*/
    while(1){
        //loop
    }
}

void printCabecera(){
    system("clear");
    printf("*************************************************************************\n");
    printf("*   Tecnólogo Informático - Redes de Computadoras 2016 - Laboratorio 1  *\n");
    printf("*                            MegaMessage - Server                       *\n");
    printf("*                        Powered by Cristian Bermudez                   *\n");
    printf("*************************************************************************\n");
    printf("\n");
}

int main(int argc, char** argv) {
    
    printCabecera();
    int PORT ;

    // Ingresar el puerto que se va a utilizar para el servicio

    printf("\tChoise what port do you what to use : ");
    std::cin >> PORT;
    system("clear");
    printCabecera();

    // Crear socket

    int fd, fd2, numberOfClients;
    struct sockaddr_in server;
    struct sockaddr_in client;
    socklen_t clilen;
    numberOfClients = 0;

    printf("Creating socket...\n");
system("sleep 1");
    if ((fd=socket(AF_INET, SOCK_STREAM,0))==-1) {
// printf("Error en socket()\n");
// return -1;
    }

    // Bind

    server.sin_family       = AF_INET;
    server.sin_port         = htons(PORT);
    server.sin_addr.s_addr  = INADDR_ANY;
    bzero(&(server.sin_zero),8);
    printf("Binding...\n");
system("sleep 1");
    if (bind(fd,(struct sockaddr*)&server,sizeof(struct sockaddr))==-1) {
// printf("Error en bind()\n");
// return -1;
    }

    // Loop infinito 1

    for (;;){

    // Listen

        printf("Linstening...\n");
system("sleep 1");    
        if (listen(fd,BACKLOG)==-1){
            printf("Error en listen()\n");
            return -1;
        }
        printf("Server inicializated...\n");
        printf("Listening on port : %d\n\n",PORT);

        while(numberOfClients < BACKLOG){
            printf("0\n");
            clilen = sizeof(client);  
            if ((fd2 = accept(fd,(struct sockaddr *) &client, &clilen)) == -1) {
                printf("Error en accept()\n");
                return -1;
            }
            printf("1\n");
            int pid;
            pid = fork();
            if (pid < 0) {
                return -1;
            }
            if (pid == 0) {
                printf("2\n");
                // close(fd);
                printf("3\n");
                processMessage(fd2);
                printf("afterprocess\n");
                return 0; // No se si necesariamente debe ir acá un return 0 y no cerrar ningún socket abierto.
            }
            // printf("You got a connection from %s\n", inet_ntoa(client.sin_addr));           // Mensaje de debug
            // send(fd2,"Bienvenido a mi servidor.\n",25,0);                                   // Mensaje que puede o no ir
            else {
                close(fd2);    
            }
        }
    }
    
    close(fd);

    // for(;;) {

    // }
    return 0;
}