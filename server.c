#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

//embedding webpage
char webpage[] =
//necessary for the browser to act based on what the server sends to the browser
"HTTP/1.1 200 OK\r\n"
"Content-Type: text/html; charset=UTF-8\r\n\r\n"
"<!DOCTYPE html>\r\n"
"<html><head><title>Server_18020569</title>\r\n"
"<style>body {background-color: #000540}</style></head>\r\n"
"<body><h1>Fuck this server</h1>\r\n"
"<img src=\"photo2.jpg\"></body></html>\r\n"

;

int main(int argc, char *argv[])
{
//socket addresses for server and client
struct sockaddr_in server_addr, client_addr;
//struct socketAddress_in serverAddress, clientAddress;

socklen_t sin_len = sizeof(client_addr);
int fd_server, fd_client;//return value from the socket function
char buf[2048];//to store return content sent by the server or browser
int fdimg; //holding the files that we open
int on = 1;

fd_server = socket(AF_INET, SOCK_STREAM, 0);

if (fd_server < 0)
{
perror("socket");
exit(1);
}

//setup socket property
setsockopt(fd_server, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int));

server_addr.sin_family = AF_INET;
server_addr.sin_addr.s_addr = INADDR_ANY;
server_addr.sin_port = htons(8080);

if(bind(fd_server, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1 ) //error
{  
perror("bind");
close(fd_server);
exit(1);
}
if(listen(fd_server,10)== -1){
perror("listen");
close(fd_server);
exit(1);
}

while(1){
fd_client = accept(fd_server, (struct sockaddr *) &client_addr, &sin_len);

if(fd_client == -1){
perror("Cant connect to client.....\n");
continue;
}

printf("Got client connection.......\n");

if(!fork()){

//childProcess
close(fd_server);

//clear buffer
memset(buf, 0, 2048);
read(fd_client, buf, 2047);

printf("%s\n", buf); //content of the buffer - what the client/browser sent

//add html embeded objects
if(!strncmp(buf, "Get /photo1.jpg", 16)) //contain what the web browser is asking for)
{
fdimg = open("photo1.jpg", O_RDONLY);
sendfile(fd_client, fdimg, NULL, 4000);
close(fdimg);
}
else if(!strncmp(buf, "GET /photo2.jpg",16))
{
fdimg = open("photo2.jpg", O_RDONLY);
sendfile(fd_client,fdimg, NULL, 6000);
close(fdimg);
}
else
//send the webpage
write(fd_client, webpage, sizeof(webpage) -1);

close(fd_client);
printf("closing....\n");
exit(0);

}
//parentProcess
close(fd_client);


}


return 0;
}
