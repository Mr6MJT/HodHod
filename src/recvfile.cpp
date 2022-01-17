#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;
int main() {

    cout << "Enter your friend's ip:  \n";
    char ip[20];
    fgets(ip, 16, stdin);
    cout << "Enter the port: \n";
    char port[6];
    fgets(port, 6, stdin);

    int sock;
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(atoi(port));
    serv.sin_addr.s_addr = inet_addr(ip);
    int con = connect(sock, (struct sockaddr*) &serv, sizeof(serv));
    if (con < 0) {
	printf("failed to connect");
	exit(1);
    }

    char filename[40];
    recv(sock, (char *)filename, 40, 0);
    int op = open(filename, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    char buff[999999];
    recv(sock, (char *)buff, 999999, 0);
    write(op, (char *)buff, strlen(buff));
    close(op);
    close(sock);
}
