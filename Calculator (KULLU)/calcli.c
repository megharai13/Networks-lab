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
        int num1,num2,ans,choice;
        
        
        while(1){
              bzero((char *)buffer,256);
              
              int n = read(sockfd,buffer,sizeof(buffer));
              if(n<0) error("Error in reading");
              
              printf("%s: ",buffer);
              scanf("%d",&num1);
              
              n =write(sockfd,&num1,sizeof(num1));
              if(n<0) error("Error in sending num1");
              
              bzero((char *)buffer,256);
              
              n = read(sockfd,buffer,sizeof(buffer));
              if(n<0) error("Error in reading");
              
              printf("%s: ",buffer);
              scanf("%d",&num2);
              
              n =write(sockfd,&num2,sizeof(num2));
              if(n<0) error("Error in sending num2");
              
              n = read(sockfd,buffer,sizeof(buffer));
              if(n<0) error("Error in reading choice");
              
              printf("%s: \n",buffer);
              printf("1. ADD\n2. SUB\n3. MUL\n4. DIV\n");
              scanf("%d",&choice);
              
              n =write(sockfd,&choice,sizeof(choice));
              if(n<0) error("Error in sending choice");
              
              if(choice==5) break;
              
              n=read(sockfd,&ans,sizeof(ans));
              if(n<0) error("Error in reading ans");
              printf("answer is : %d\n",ans);
              printf("\n");
              }
           close(sockfd);
           return 0;     
          }
              
              
              
              
              
              
              
              
              
              
              
              
              
