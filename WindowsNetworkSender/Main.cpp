#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<algorithm>
#include<conio.h>
#include<stdio.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

int main(int argc, char* argv[])
{
	WSADATA wsa;
	SOCKET s; 
	const char* message = nullptr;
	const int maxReply = 4096; 
	char serverReply[maxReply];
	int recv_size;

	//char* server

	printf("Initialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return 1;
	}

	printf("Initialised.\n");

	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d\n", WSAGetLastError());
	}

	printf("Socket created.\n");

	struct sockaddr_in server;
	// IPv4 AF_INET sockets:

	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(7000);


	//connect to remote server. 

	if (connect(s, (struct sockaddr*) &server, sizeof(server)) < 0)
	{
		puts("Connection fucked.");
	}
	else
	{
		puts("Connection successed!");
	}
	
	message = "GO FUCK YOURSELF";
	if (send(s, message, strlen(message), 0) < 0)
	{
		puts("Didn't send your ballbag message...\n");
	}
	else
	{
		puts("Data motherfucking sennnnttt!\n");
	}

	if ((recv_size = recv(s, serverReply, maxReply, 0)) == SOCKET_ERROR)
	{
		puts("Server sent nothing back the cunts.\n");
	}
	else
	{
		puts("Here's your data you filthy animal...\n");
		if (recv_size > maxReply)
		{
			serverReply[maxReply -1] = '\0';
		}
		else
		{
			serverReply[recv_size] = '\0';
		}
		puts(serverReply);
	}
	

	
	while(!_kbhit())
	{
		
	}
	closesocket(s);
	WSACleanup();

	return 0;
}