// coded by Mr MJT
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
using namespace std;

struct sockaddr_in server;

int main() {
    cout << "Enter your friend's ip:  \n";
    char ip[20];
    fgets(ip, 16, stdin);
    cout << "Enter the port: \n";
    char port[6];
    fgets(port, 6, stdin);
    cout << "\n";
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0)
    {
        cout << "Socket() not created\n";
        exit(1);
    }
  // Socket created
   cout << "Socket() created\n";
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_port = htons(atoi(port));
    memset(&server.sin_zero, 0, 8);
    int con = connect(sock, (struct sockaddr*) &server, sizeof(server));
    if (con < 0)
    {
	cout << "Doesnot connected\n";
	exit(1);
    }
    // Connected
    cout << "Connected\n";
    system("clear");
    for (int i = 0; i < 999999; i++)
    {
        memset(buffer, 0x00, 1024);
        memset(text, 0x00, 1024);
    	system("bash red");
    	cout << "\n";
    	// Waiting your friend's message
        printf("your friend is typing..\n");
    	char buffer[1024];
    	int r = recv(sock, buffer, 1024, 0);
    	printf("RECV: %s\n", buffer);
    	system("bash white");
    	cout << "\n";
     	printf("SEND: ");
        char text[1024];
        fgets(text, 1024, stdin);
    	int s = send(sock, text, strlen(text), 0);
        memset(buffer, 0x00, 1024);
        memset(text, 0x00, 1024);
    }
    // Close the socket
    close(sock);
}
