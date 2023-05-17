#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>


void error(char *msg){
 
 perror(msg);
 exit(1);
 
 }
 
int main(int argc,char *argv[]){

           if(argc<2) error("port not found");
           
           int portno = atoi(argv[1]);
           
           int sockfd = socket(AF_INET,SOCK_STREAM,0);
           if(sockfd<0) error("Opening problem in socket");
                      
           struct sockaddr_in serv_addr,cli_addr;
           
           bzero((char *)&serv_addr,sizeof(serv_addr));
             
           serv_addr.sin_family = AF_INET;
           serv_addr.sin_addr.s_addr = INADDR_ANY;
           serv_addr.sin_port = htons(portno);
           
           if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0) error("Binding problem");
           
           listen(sockfd,3);
           socklen_t clilen= sizeof(cli_addr);
           
           int newsockfd = accept(sockfd,(struct sockaddr*)&cli_addr,&clilen);
           
           if(newsockfd<0) error("Accepting problem");
           
           int num1,num2,ans,choice;
           
           while(1){
               int n=write(newsockfd,"Enter num 1: ",sizeof("Enter num 1: "));
               if(n<0) error("writing problem");
               
               n = read(newsockfd,&num1,sizeof(num1));
               if(n<0) error("error in num1 reading");
               printf("num1 is :%d\n",num1);
               
               n = write(newsockfd,"Enter num  2: ",sizeof("Enter num  2: "));
               if(n<0) error("writing in 2");
               n = read(newsockfd,&num2,sizeof(num2));
               
               if(n<0) error("error in reading num2");
               printf("num2 is : %d\n",num2);
               
               n = write(newsockfd,"Enter choice :",sizeof("Enter choice :"));
               if(n<0) error("error in choice");
               
               n = read(newsockfd,&choice,sizeof(choice));
               if(n<0) error("error in choice reading");
               printf("Entered choice is :%d\n",choice);
               switch(choice){
                        case 1:
                        ans=num1+num2;
                        break;
                       
                        case 2:
                        ans=num1-num2;
                        break;
                       
                        case 3:
                        ans=num1*num2;
                        break;
                        
                        case 4:
                        ans=num1/num2;
                        break;
                        
                        case 5:
                        break;
                }
               if(choice==5) break;
               n = write(newsockfd,&ans,sizeof(ans));
               if(n<0) error("writing problem in ans");
               printf("ans : %d\n",ans);
         }
         close(sockfd);
         close(newsockfd);
         return 0;         
 }
           
