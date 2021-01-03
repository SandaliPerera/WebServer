#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <fontl.h>
#include <sys/stat.h>

//embedding webpage
char webpage[] =
//necessary for the browser to act based on what the server sends to the browser
"HTTP/1.1 200 OK\r\n"
"Content-Type: text/html; charset=UTF-8\r\n\r\n"
"<!DOCTYPE html>\r\n"
;

int main(int argc, char *argv[])
{
	//socket addresses for server and client
		struct socketaddr_in server_addr, client_addr;
		//struct socketAddress_in serverAddress, clientAddress;

		socklen_t sin_len = sizeof(clientAddress);
		int fd_server, fd_client;//return value from the socket function
		char buf[2048];//to store return content sent by the server or browser 	
		int fdimg; //holding the files that we open
		int on = 1; 
		
		fd_server = socket((AF)INET, SOCK_STREAM, 0)
		
		if (server < 0)
		{
			perror("socket");
			exit(1);
		}
		
		//setup socket property
		setsocketpt(fd_server, SOL_SOCKET, SO_RESUREADDR, &on, sizeof(int));

		server_addr.sin_family = AF_INET;
		server_addr.sin_addr.s_addr = INADDR_ANY;
		server_addr.sin_port = htons(8080); 
		
		if(bined(fd_server, (struct socketaddr *) &server_addr, sizeof(server_addr)) == -1 ) //error
		{  
			perror("bind");
			close(fd_server);
			exit(1);
		}
		
		
		return 0;
}	
