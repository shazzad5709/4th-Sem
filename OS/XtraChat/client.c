#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>

#define PORT 5050       // the port client will be connecting to 
#define MAXDATASIZE 256 // max number of bytes we can get at once 

char client_name[20];    //cpmmecn

void *dostuff (void *socket_desc)
{
  char *str, buffer[MAXDATASIZE];
  int sock = *(int*)socket_desc,numbytes;
    
   while(1){
        bzero(buffer,MAXDATASIZE);
        if ((numbytes=read(sock, buffer, MAXDATASIZE-1)) < 0) {
            perror("ERROR reading from socket");  
            exit(0);  
        }
        buffer[numbytes] = '\0';

        printf("From: %s\n",buffer);
    }

}


int main(int argc, char *argv[])
{
    int socket_fd, numbytes;  
    char buf[MAXDATASIZE],temp[MAXDATASIZE];
    struct hostent *server;
    struct sockaddr_in server_addr; // connector's address information 
    pthread_t thread_num;

    if (argc != 3) {
        printf("usage: client hostname and name\n"); 
        exit(1);  
    }
    

    if ((server=gethostbyname(argv[1])) == NULL) {  // get the host info 
        printf("ERROR, no such host\n");  
        exit(0);  
    }

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("ERROR opening socket");  
        exit(0);  
    }

    bzero((char *) &server_addr, sizeof(server_addr));  // zero the rest of the struct 
    server_addr.sin_family = AF_INET;    // host byte order 
    server_addr.sin_port = htons(PORT);  // short, network byte order 
    server_addr.sin_addr = *((struct in_addr *)server->h_addr);

    if (connect(socket_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) < 0) {
        perror("ERROR connecting");  
        exit(0);  
    }

    if (write(socket_fd,argv[2],strlen(argv[2])) < 0) {        //sent client name to server
        perror("ERROR writing to socket"); 
        exit(0);  
    }


   if( pthread_create( &thread_num , NULL ,  dostuff , (void*) &socket_fd) < 0) {           //create thread for read
        perror("ERROR create thread"); 
        exit(1);  
    }

    while(1){
        bzero(buf,MAXDATASIZE);
        fgets(buf,MAXDATASIZE-1,stdin);

        if(strcmp(buf,"exit\n")==0){
            printf("Close connection\n");
            pthread_exit(&thread_num);
            close(socket_fd);
            exit(0);
        }
    
        if (write(socket_fd,buf,strlen(buf)) < 0) {
            perror("ERROR writing to socket"); 
            exit(0);  
        }
    }

    close(socket_fd);
    return 0;
}

