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

#define PORT 8090
#define MAXDATASIZE 5000 // Numero maximo de datos en bytes

using namespace std;

void printCabecera(){
    system("clear");
    printf("*************************************************************************\n");
    printf("*   Tecnólogo Informático - Redes de Computadoras 2016 - Laboratorio 1  *\n");
    printf("*                            MegaMessage - Client                       *\n");
    printf("*                        Powered by Cristian Bermudez                   *\n");
    printf("*************************************************************************\n");
    printf("\n");
}

void printMenu(){
    printf("\t1 - Inciar sesión\n");
    printf("\t0 - Cerrar sesión\n");
    printf("\n");    
}

void login(string serverName, int serverPort, string userName){
/*
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    printf("Please enter the message: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,256);
    n = read(sockfd,buffer,255);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%s\n",buffer);
    close(sockfd);
    return 0;
*/
    int fd, numbytes, byte;
    char buffer[MAXDATASIZE];

    struct hostent * he;
    struct sockaddr_in server;

    const char * serverNameChar = serverName.c_str();

    if ((he=gethostbyname(serverNameChar))==NULL) {
        throw "gethostbyname() error";
    }

    if ((fd=socket(AF_INET, SOCK_STREAM, 0))==-1) {
        throw "socket() error";
    }

    server.sin_family   = AF_INET;
    server.sin_port     = htons(serverPort);
    server.sin_addr     = *((struct in_addr *) he -> h_addr);
    bzero(&(server.sin_zero),8);

    if(connect(fd, (struct sockaddr *)&server, sizeof(struct sockaddr))==-1) {
        throw "connect() error";
    }

    // Una vez realizada la conexion, envío el nombre del usuario al server para que lo almacene.

    const char * userNameChar = userName.c_str();
    byte = write(fd,userNameChar,userName.length());
    if (byte < 0) {
        throw "Error writing to socket";
    }
    while(1) {
/*        printf("Client: Enter Data for Server:\n");
        fgets(buf,MAXDATASIZE-1,stdin);
        if ((send(fdsrv,buf, strlen(buf),0))== -1) {
                fprintf(stderr, "Failure Sending Message\n");
                close(fdsrv);
                exit(1);
        }
        else {
                printf("Client:Message being sent: %s\n",buf);
                numbytes = recv(fdsrv, buf, sizeof(buf),0);
                if ( numbytes <= 0 )
                {
                        printf("Either Connection Closed or Error\n");
                        //Break from the While
                        break;
                }
                buf[numbytes] = '\0';
                printf("Client:Message Received From Server -  %s\n",buf);
           }
*/    }

    // bzero(buffer,MAXDATASIZE);
    // fgets(buffer,MAXDATASIZE - 1,stdin);

/*
        connect(sConnect, (SOCKADDR*)&addr, sizeof(addr));
        antwoord = recv (sConnect, bericht, sizeof(bericht), NULL);
        strbericht = bericht;
        cout << strbericht << chatname <<endl;
*/

    // byte = write(fd,buffer,strlen(buffer));
    // if (byte < 0) {
        // throw "Error writing to socket";
    // }
    // byte = send(fd,userName,sizeof(userName),NULL);
    
   
// antwoord = send(sConnect, chatname, sizeof(chatname), NULL);

    // bzero(buffer,MAXDATASIZE);
    // byte = read(fd,buffer,MAXDATASIZE - 1);


    // if (byte < 0) {
        // throw "Error reading to socket";  
    // }
    // else {
        // buffer[numbytes]='\0';
        // printf("Server Message : %s\n", buffer);
    // } 
    // printf("%s\n",buffer);
    close(fd);
/*
    if((numbytes=recv(fd,buf,MAXDATASIZE,0))==-1){
        throw "recv() error";
    }

    close(fd);
*/
}

int main(int argc, char** argv) {
    bool exitMenu = false;
    while (!exitMenu) {
        printCabecera();       
        printMenu();
        int option;
        scanf("%d",&option);
        switch(option) {
            case 1: {
                system("clear");
                string serverName;
                printf("\n\tIngrese la URL del Servicio : ");
                std::cin >> serverName;
                system("clear");
                int serverPort;
                printf("\n\tIngrese el Puerto del Servicio : ");
                std::cin >> serverPort;
                system("clear");
                string userName;
                printf("\n\tIngrese el Nombre de Usuario : ");
                std::cin >> userName;
                try {
                    login(serverName, serverPort, userName);
                } 
                catch (const char * e) {
                    system("clear");
                    cerr << "\tHa ocurrido un error ! : " << e;
                    cout << "\n\n\tPresione Enter para Continuar";
                    getchar();
                    getchar();
                }
                break;
            }
            case 0: {
                exitMenu = true;
                break;
            }
            default: {
                printf("\nOpción Incorrecta\n");
                system("sleep 2");
                system("clear");
            }
        }
    }
}