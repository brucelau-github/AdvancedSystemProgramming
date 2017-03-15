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
#define PYTHONCMD "python simplep.py"
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
		int status,pid;
		clilen = sizeof(cliAddr);
		clientsock = accept( sock, (struct sockaddr *)&cliAddr, &clilen);
		printf("A client connected.\n");
		if(clientsock < 0) {
			perror("fail to address");
			exit(EXIT_FAILURE);
		} 
		
		//fork a child process to do the task; parent will accept another connection.
		if( (pid=fork()) == 0) {
		
			//read data
			int n;
			char buf[BUFLEN];
			unlink(FILENAME);
			FILE *fp;
			fp = fopen(FILENAME, "w+");
			printf("receiving image data.\n");
			while( (n = recv(clientsock, buf, BUFLEN, 0)) > 0 ) {
				//write(STDOUT_FILENO, buf, n);
				//printf("\33[2k\r finished %d percent.", 20);
				printf(".");
				fwrite(buf, 1, n, fp);
			}
			fclose(fp);
			if(n < 0) perror("recv error\n");
			printf("finished!\n");

			//execute python
			FILE *cmdpipe;
			char stdoutbuff[1035];

			cmdpipe = popen( PYTHONCMD, "r" );
			if(cmdpipe == NULL) {
				printf("Failed to run python command.\n");
				exit(EXIT_FAILURE);
			}

			while (fgets(stdoutbuff, sizeof(stdoutbuff)-1, cmdpipe)) {
				printf("%s\n",stdoutbuff);
			}
			pclose(fp);

			//close socket
			close(clientsock);
			exit(EXIT_SUCCESS);
		}
		//parent process.
		//waitpid( pid, &status, WNOHANG);
		waitpid( -1, &status, WNOHANG); //wait for any child

	}
		


}
