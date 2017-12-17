
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sendfile.h>

char *page200 = "HTTTP/1.1 200 OK\nContent-Type: text/html; charset=UTF-8\r\n";
char *page404 = "HTTTP/1.1 404 Not found\nContent-Type: text/html; charset=UTF-8\r\n";
char *page403 = "HTTTP/1.1 403 Read Error\nContent-Type: text/html; charset=UTF-8\r\n";

/*
char webpage[]=
"HTTTP/1.1 200 OK\r\n"
"Content-Type^ text/html; charset=UTF-8\r\n\r\n"
"<!DOCTYPE html>\r\n"
"<html<head><title>ShellWaveX</title>|\r\n"
*/


int main ( int argc, char* argv[] )
{
	struct sockaddr_in server_addr, client_addr;
	socklen_t sin_len = sizeof(client_addr);
	int fd_server , fd_client;
	char buf[2048];
	int fdimg;
	int on = 1;
	fd_server = socket(AF_INET , SOCK_STREAM, 0 );
	if( fd_server < 0 )
	{
	perror("sokket");
	exit(1);
	}	
	
	setsockopt(fd_server, SOL_SOCKET, SO_REUSEADDR, &on ,sizeof(int));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(8080);
	
	if( bind (fd_server, (struct sockaddr *)  &server_addr, sizeof(server_addr))== -1 )
	{
	perror("bind");
	close(fd_server);
	exit(1);	
	}
	
	if ( listen(fd_server, 10) == -1)
	{
	perror("listen");
	close(fd_server);
	exit(1);
	}
	
	while(1){
	fd_client = accept( fd_server, (struct sockaddr *) &client_addr, &sin_len);
	if(fd_client == -1);
	perror("Error in connection to client server\n'");
	fdimg = open("404.html", O_RDONLY);
	sendfile(fd_server, fdimg, NULL, 4000);
	close(fdimg);
	continue;
	}
	
	printf("Got client connection\n");
	
	if(!fork())
	{
	close(fd_server);
	memset(buf, 0, 2048);
	read(fd_client, buf, 2047);
	
	printf("%s\n", buf);
	
	if(!strncmp(buf, "GET /index.html", 16)){
	
	fdimg = open("index.html", O_RDONLY);
	sendfile(fd_client, fdimg, NULL, 4000);
	close(fdimg);
    }
    else
    write(fd_client, page200, sizeof(page200) -1);
	close(fd_client);
	printf("closing...\n");
	exit(0);
	}
	close(fd_client);
	
	
	return 0;
}
