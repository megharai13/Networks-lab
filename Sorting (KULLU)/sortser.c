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
 
 void sortList(int list[],int num1){
       for(int i=0; i<num1; i++){
           int minInd=i;
           for(int j=i; j<num1; j++){
                    if(list[j]<list[minInd]){
                           minInd=j;
                  }
               }
           int a=list[i];
           list[i]=list[minInd];
           list[minInd]=a;
           }
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
           
           int num1;
           int list[100];
           
           while(1){
               int n=write(newsockfd,"Enter size of list  ",sizeof("Enter size of list "));
               if(n<0) error("writing problem");
               
               n = read(newsockfd,&num1,sizeof(num1));
               if(n<0) error("error in num1 reading");
               printf("size is :%d\n",num1);
               
               if(num1<=0) break;
               
               n = write(newsockfd,"Please Enter the elements in the list: ",sizeof("Please Enter the elements in the list: "));
               if(n<0) error("writing in 2");
               
               n = read(newsockfd,list,sizeof(list));
               
               printf("Elements are: \n");
               for(int i=0; i<num1; i++) printf("%d ",list[i]);
               printf("\n\n");
               
               sortList(list,num1);
               printf("Sorted list is : \n");
               for(int i=0; i<num1; i++) printf("%d ",list[i]);
               printf("\n");
              
               n = write(newsockfd,list,sizeof(list)); 
               if(n<0) error("error in sending updated list");
               
               printf("\n\n");
         }
         close(sockfd);
         close(newsockfd);
         return 0;         
 }
           
