#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<netinet/in.h>
#include<netdb.h>


void error(const char *msg){

   perror(msg);
   exit(0);
   
}

int main(int argc,char *argv[])
{
      int sockfd, portno, n;
      struct sockaddr_in serv_addr;
      struct hostent *server;
      
      char buffer[255];
      
      if(argc<3){
      fprintf(stderr,"usage %s hostname or port\n",argv[0]);
      exit(1);
      }
      
      portno = atoi(argv[2]); 
      
      sockfd = socket(AF_INET,SOCK_STREAM,0);
      
      if(sockfd<0) error("Error in opening socket");
      
      server = gethostbyname(argv[1]);
      
      if(server==NULL){
           error("no such host found");
      }   
      
       bzero((char *)&serv_addr,sizeof(serv_addr));
       serv_addr.sin_family = AF_INET;
       bcopy(server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
       serv_addr.sin_port = htons(portno);
       if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
       error("Connection failed");
       while(1){
        bzero(buffer,sizeof(buffer));
        fgets(buffer,sizeof(buffer),stdin);
        n = write(sockfd , buffer , strlen(buffer));
        if(n<0) error("Error in writing");
        bzero(buffer,sizeof(buffer));
        n= read(sockfd,buffer,255);
        if(n<0) error("Error in reading");
        printf("Server : %s\n",buffer);
        
        int i = strncmp("Bye", buffer,3);
        if(i==0) 
        break;
        
        }
        close(sockfd);
        return 0;
        }
       
