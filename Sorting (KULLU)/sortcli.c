#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<netdb.h>

void error(char *msg){
  perror(msg);
  exit(1);
  
  }
  
 int main(int argc,char *argv[]){
 
        if(argc<3) error("either port or ip is missing");
        
        int portno = atoi(argv[2]);
    
        
        int sockfd = socket(AF_INET,SOCK_STREAM,0);
        if(sockfd<0) error("open socket error");
        
        struct hostent *server = gethostbyname(argv[1]);
        struct sockaddr_in serv_addr;
        
        serv_addr.sin_family = AF_INET;
        bcopy(server->h_addr,(struct sockaddr *)&serv_addr.sin_addr.s_addr,server->h_length);
        serv_addr.sin_port = htons(portno);
        
        if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0) error("Connection fails");
        
        char buffer[256];
        int num1;
        int list[100];
        
        
        while(1){
              bzero((char *)buffer,256);
              
              int n = read(sockfd,buffer,sizeof(buffer));
              if(n<0) error("Error in reading");
              
              printf("%s: ",buffer);
              scanf("%d",&num1);
              
              n =write(sockfd,&num1,sizeof(num1));
              if(n<0) error("Error in sending num1");
              
              if(num1<=0) break;
              
              bzero((char *)buffer,256);
              
              n = read(sockfd,buffer,sizeof(buffer));
              if(n<0) error("Error in reading");
              
              printf("%s: \n",buffer);
              for(int i=0; i<num1; i++) scanf("%d",&list[i]);
                 
              printf("\n");
              
              n=write(sockfd,list,sizeof(list));
              if(n<0) error("error in writing list");
              
              n = read(sockfd,list,sizeof(list));
              if(n<0) error("Could not get the updated list");
              
              printf("Updated list is: \n");
              
              for(int i=0; i<num1; i++) printf("%d ",list[i]);
              printf("\n\n");
              }
           close(sockfd);
           return 0;     
          }
              
              
              
              
              
              
              
              
              
              
              
              
              
