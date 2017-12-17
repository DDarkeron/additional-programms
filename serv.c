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
	char server_message[256] = "You have reached the server!";
    //create the server socket
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	//define server address
	struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;
	
	//bind the socket to our spicified IP and port
	bind(server_socket,(struct sockaddr *), &server_address, sizeof(server_address));
	
	listen(server_socket, 10);
	
	int client_socket;
	int client_socket = accept(server_socket, (struct sockaddr *), sizeof(server_address));
	
	
	send(client_socket, server_message, siZeof(server_message), 0);
	
	close(server_socket);

	
	
	
	
	
	
return 0;	
}
