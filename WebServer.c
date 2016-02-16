/*
	Program 1
	by: Olivia Hughes and Satvir Singh 
*/
#include<stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>

int main()
{
	int portnoS, Socket2;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int cLength;
	char httprequest[50];
	struct cli_addr;
	
	int cSocket = socket(AF_INET, SOCK_DGRAM, 0);//Create a socket
	if(cSocket<0) //print error and exit if socket is not created
	{
		error("Error creating socket!"); 
		exit(1);
	}
	printf("Socket Created");
	bind(cSocket, (struct sockaddr *) &serv_addr, sizeof(serv_addr));//bind to port number 80
	
	listen(cSocket,1);//listen for connection
	cLength = sizeof(cli_addr);//get address length
	Socket2 = accept(cSocket, (struct sockaddr *) &cli_addr, &cLength);//accept connection
	system("firefox cse05.cse.unt.edu");
	return 0;
}