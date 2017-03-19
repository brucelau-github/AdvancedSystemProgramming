#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <signal.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define SERVER_PORT 5000
#define BUFLEN 300
#define FILENAME "/tmp/infer_img"
#define PY_SERVER_PID_FILE "/tmp/py_server_pid"
#define PYTHONCMD "python simplep.py"

void eventhandler() {
	exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]){
	
	int sock, clientsock;
	struct sockaddr_in cliAddr,srvAddr;
	//register signal event
	signal(SIGINT, eventhandler);
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
				printf(".");
				fwrite(buf, 1, n, fp);
				if(n < BUFLEN) break;
			}
			fclose(fp);
			if(n < 0) perror("recv error\n");
			printf("finished!\n");
			//save pidinfo
			fp = fopen("/tmp/cli_pid","w");
			bzero(buf,sizeof(buf));
			sprintf(buf,"%d",getpid());
			fwrite(buf, strlen(buf), 1, fp);
			fclose(fp);
			
			//send a signal to py_server
			fp = fopen(PY_SERVER_PID_FILE,"r");
			if(fp == NULL ) {
				printf("Failed to open %s.\n",PY_SERVER_PID_FILE);
				exit(EXIT_FAILURE);
			}
			char pidbuffer[100];
			fread(pidbuffer,sizeof(pidbuffer),1,fp);
			fclose(fp);
			kill( atoi(pidbuffer), SIGUSR1); 

			//wait for py server signal
			pause();

			//read the output 
			FILE *outfp;
			outfp = fopen("/tmp/py_server_out","r");
			char outbuffer[5000];
			fread(outbuffer, sizeof(outbuffer), 1, outfp);
			printf("the content of the file is %s",outbuffer);
			send(clientsock, outbuffer, strlen(outbuffer), MSG_CONFIRM);
			fclose(outfp);


			//close socket
			close(clientsock);
			exit(EXIT_SUCCESS);
		}
		//parent process.
		//waitpid( pid, &status, WNOHANG);
		waitpid( -1, &status, WNOHANG); //wait for any child

	}
		


}
