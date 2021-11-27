#include <string.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
using namespace std;
struct sockaddr_in server;
int main() {
    cout << "Enter your ip:  \n";
    char ip[20];
    fgets(ip, 16, stdin);
    cout << "Enter the port: \n";
    char port[6];
    fgets(port, 6, stdin);
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0)
    {
	cout << "Socket() not created\n";
	exit(1);
    }
    cout << "Socket() created\n";
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_port = htons(atoi(port));
    memset(&server.sin_zero, 0, 8);
    int bnd = bind(sock, (struct sockaddr*) &server, sizeof(server));
    if (bnd < 0)
    {
	    cout << "Bind() error\n";
            exit(1);
    }
    cout << "Binded to the local address\n";
    int nRet = listen(sock, 5);
    if (nRet < 0)
    {
	    cout << "Listen() error";
            exit(1);
    }
    cout << "Started listining\n";
    int c = sizeof(struct sockaddr_in);
    int acc = accept(sock, (struct sockaddr*) &server, (socklen_t*)&c);
    if (acc < 0)
    {
	    cout << "Accept() failed\n";
	    exit(1);
    }
    cout << "Accepted succesfully\n";
    system("clear");
    while (1)
    {
	system("bash white");
	cout << "--Enter text to send: \n";
	cout <<">> ";
	char text[500];
	fgets(text, 500, stdin);
	send(acc, text, strlen(text), 0);
	system("bash red");
	cout << "---Waiting your friend's message---\n";
	char buffer[500];
	recv(acc, buffer, 500, 0);
	cout << "--New message recieved: " << buffer; 
	text[500] = {0};
	buffer[500] = {0};
   }
    close(acc);
}
