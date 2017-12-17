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


int main(int argc, char *argv[])
{
	FILE *file;
	file = fopen("index.html","r");
	char response_data[128];
	fgets(response_data, 128, file);
	
	char http_header[256] = "HTTP/1.1 200 OK\r\n\n";
	
	strcat(http_header, response_data);
	
	int server_socket;
	
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(8080);
	server_address.sin_addr.s_addr = INADDR_ANY;
	
	if( bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address))== -1 )
        {
        perror("can't bind");
        close(server_socket);
        exit(1);
	}
	if(listen(server_socket, 10)== -1)
        {
        perror("can't listen");
        close(server_socket);
        exit(1);
        }

	int client_socket;
	while(1)
	{
	client_socket = accept(server_socket, NULL, NULL);
        if(client_socket == -1){
        perror("Connection failed...\n");
        continue; 

        }
        printf("Got connection...\n");
	send(client_socket, http_header, sizeof(http_header), 0);
        close(client_socket);
        printf("closing...\n");
	exit(0);
	}
	
return 0;	
}
