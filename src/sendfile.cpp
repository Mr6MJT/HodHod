#include <cstring>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
using namespace std;

int main() {
    cout << "Enter your friend's ip:  \n";
    char ip[20];
    fgets(ip, 16, stdin);
    cout << "Enter the port: \n";
    char port[6];
    fgets(port, 6, stdin);
    int sock, bnd, nret, acc;
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(atoi(port));
    serv.sin_addr.s_addr = inet_addr(ip);
    bnd = bind(sock, (struct sockaddr*) &serv, sizeof(serv));
    if (bnd < 0) {
	printf("failed to bind");
	exit(1);
    }
    nret = listen(sock, 5);
    if (nret < 0) {
	printf("failed to listen");
    }
    int c = sizeof(struct sockaddr_in);
    acc = accept(sock, (struct sockaddr*) &serv, (socklen_t*)&c);
    if (acc < 0) {
	printf("failed to accept");
    }

    printf("enter filename [with .txt]:");
    char filename[40];
    fgets(filename, 40, stdin);
    send(acc, filename, 40, 0);


    char buff[999999];
    int op = open(filename, O_RDONLY, S_IRUSR | S_IWUSR);
    read(op, (char *)buff, 999999);
    send(acc, buff, 999999, 0);
    close(op);
    close(sock);
}
