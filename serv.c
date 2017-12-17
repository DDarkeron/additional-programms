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

int main()
{
	FILE *file;
	file fopen("index.html","r");
	char response_data[1024];
	fgets(response_data, 1024, file);
	
	char header[2048] = "HTTP/1.1 200 OK\r\n\r\n";
	//unite the string
	strcat(header, response_data);
	
	int server_socket;
	
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in server_address;
	server_address.sin_famile = AF_INET;
	server_address.sin_port = htons(8080);
	server_address.sin_addr = INADDR_ANY;
	
	bind(server_socket, (struct sockaddr*) &server_address, sizeod(server_address));
	
	listen(server_socket, 10);
	int client_socket;
	while(1)
	{
	client_socket = accept(server_socket, NULL , NULL);
	send(client_socket, header, sizeof(header), 0);
	close(client_socket);	
	}
	
	
	/*
	char server_message[256] = "You have reached the server!";
    
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;
	
	bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
	
	listen(server_socket, 10);
	
	int client_socket;
	client_socket = accept(server_socket, NULL , NULL);
	
	
	send(client_socket, server_message, sizeof(server_message), 0);
	
	close(server_socket);*/
	
return 0;	
}
