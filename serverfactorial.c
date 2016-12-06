#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>

#include <string.h>

int main( int argc, char *argv[] ) {
   int sockfd, newsockfd, portno, clilen;
   char buffer[256];
   struct sockaddr_in serv_addr, cli_addr;
   int  n;
   
   /* First call to socket() function */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }
   
   /* Initialize socket structure */
   bzero((char *) &serv_addr, sizeof(serv_addr));
   portno = 5003;
   
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);
   
   /* Now bind the host address using bind() call.*/
   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR on binding");
      exit(1);
   }
      
   /* Now start listening for the clients, here process will
      * go in sleep mode and will wait for the incoming connection
   */
   
   listen(sockfd,5);
   clilen = sizeof(cli_addr);
   
   /* Accept actual connection from the client */
   newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
	
   if (newsockfd < 0) {
      perror("ERROR on accept");
      exit(1);
   }
   
   /* If connection is established then start communicating */
   bzero(buffer,256);
   n = read( newsockfd,buffer,255 );
   int num=0;
   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }
   /*int num=atoi(buffer);*/
   printf("Here is the number: %s\n",buffer);
   /*printf("number is:%d\n",num);*/
   int i,factorial;
   factorial=1;
   sscanf(buffer,"%d",&num);
   if (buffer < 0)
           printf("Error! Factorial of a negative number doesn't exist.");

       else
       {
           for(i=num; i>0; i--)
           {
               factorial *= i;              // factorial = factorial*i;
           }
           /*fac=&factorial;*/
           /*n = send(newsockfd,fac,5,0);*/
       }
   /*printf("factorial is:%d\n",factorial );*/
   sprintf(buffer,"%d",factorial);
   
   /* Write a response to the client */
   n = write(newsockfd,buffer,sizeof(buffer));
   
   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }
      
   return 0;
}


