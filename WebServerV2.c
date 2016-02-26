#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <netinet/in.h>

#include <string.h>

int main( int argc, char *argv[] ) {
   int socket1, socket2, portno, clilen;
   FILE *webAddress;
   char buffer[256];
   struct sockaddr_in serv_addr, cli_addr;
   int  n;
   char line[80];
   long elapsed_Seconds;
   /* Creating a socket */
   socket1 = socket(AF_INET, SOCK_STREAM, 0);
   
   if (socket1 < 0) {
      printf("ERROR while opening the socket\n");
      exit(1);
   }
   
   /* Initializing the socket structure */

   portno = 8081;
   
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);
   
   /* Binding the socket to the port*/
   if (bind(socket1, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      printf("ERROR while binding\n");
      exit(1);
   }
      
   /* Begin listening for incoming connections
   */
   
   listen(socket1,5);
   clilen = sizeof(cli_addr);
   
   /* Accept connection request from the client */
   socket2 = accept(socket1, (struct sockaddr *)&cli_addr, &clilen);
	
   if (socket2 < 0) {
      printf("ERROR on accept\n");
      exit(1);
   }
   /* Begin communication */
   bzero(buffer,256);
   n = read( socket2,buffer,255 );
   
   if (n < 0) {
      printf("ERROR reading from socket\n");
      exit(1);
   }
   recv(socket2, buffer, sizeof(buffer),0);
   printf("Relayed  message: %s\n",buffer);
   printf("Opening file");
   char req[] = "HTTP/1.1 200 OK\nContent-type: text/html\n\n";
   
   char mess[] = "<html><body><H1>Error: Invalid Address</H1></body></html>";
   
	webAddress = fopen(buffer, "r");
   /* Write a response to the client */
   printf("Moving file contents");
   char *webContent = malloc((sizeof(webAddress)+1)*sizeof(char));
   //This part segmentation faults
   //fread(webContent, (sizeof(&webAddress)+1)/sizeof(char), 1, webAddress);
   /*while(fgets(line,80,webAddress)!=NULL)
   {
   		sscanf(line);
   }*/
   
   //n = write(socket2,webContent,sizeof(webContent));
   n = write(socket2,req,sizeof(req));
   n = write(socket2,mess,sizeof(mess));
   
   if (n < 0) {
      printf("ERROR writing to socket\n");
      exit(1);
   }
   close(socket1);   
   return 0;
}