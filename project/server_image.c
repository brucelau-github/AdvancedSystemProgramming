#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define SERVER_PORT 5000
#define BUFLEN 300
#define FILENAME "upload.img"
int main(int argc, char *argv[]){
	
	int sock, clientsock;
	struct sockaddr_in cliAddr,srvAddr;
	
	/*create socket*/
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("fail to create a socket");
		exit(EXIT_FAILURE);
	}
	
	srvAddr.sin_family = AF_INET;
	srvAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	srvAddr.sin_port = htons(SERVER_PORT);

	//bind server address
	if(bind(sock, (struct sockaddr *)&srvAddr, sizeof(srvAddr)) < 0 ) {
		perror("fail to address");
		exit(EXIT_FAILURE);
	}

	listen(sock, 50);
		
	while(1) {
		//start to read data from clients
		printf("%s: start to wait connetions from client on TCP port %u\n", argv[0] , SERVER_PORT);
		int clilen;
		clilen = sizeof(cliAddr);
		clientsock = accept( sock, (struct sockaddr *)&cliAddr, &clilen);
		if(clientsock < 0) {
			perror("fail to address");
			exit(EXIT_FAILURE);
		} 
		
		//fork a child process to do the task; parent will accept another connection.
		if(fork() == 0) {
		
			//read data
			int n;
			char buf[BUFLEN];
			unlink(FILENAME);
			FILE *fp;
			fp = fopen(FILENAME, "w+");
			while( (n = recv(clientsock, buf, BUFLEN, 0)) > 0 ) {
				write(STDOUT_FILENO, buf, n);
				fwrite(buf, 1, n, fp);
			}
			if()
			fclose(fp);
			if(n < 0) perror("recv error\n");
		}

	}
		


}
