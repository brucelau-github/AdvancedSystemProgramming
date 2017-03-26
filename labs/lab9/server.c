#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define SERVER_PORT 5000
#define BUFLEN 300
void exitEvent(){
	printf("exit\n");
	exit(0);
}
void childprocess(int sockd);
int main(int argc, char *argv[]){
	
	int sock, clientsock;
	struct sockaddr_in cliAddr,srvAddr;
	signal(SIGINT,exitEvent);	
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
		//child retrun status
		int status;
		int clilen;
		clilen = sizeof(cliAddr);
		clientsock = accept( sock, (struct sockaddr *)&cliAddr, &clilen);
		if(clientsock < 0) {
			perror("fail to address");
			exit(EXIT_FAILURE);
		} 
		
		//fork a child process to do the task; parent will accept another connection.
		if(fork() == 0) {
			childprocess(clientsock);
			close(clientsock);
			exit(EXIT_SUCCESS);
		}
		//wait no hangup 
		waitpid(-1,&status,WNOHANG);

	}
	
}
void childprocess(int socketd) {
	
	//print a messge
	printf("connected a client!");
	//read data,initailise the variable;
	int n,sum;
	char buf[BUFLEN],sumstr[200]; //sum to string
	sum = 0;
	while(1) {
		//clear buffer
		bzero(buf,BUFLEN);
		//receive integer from client
		n = recv(socketd, buf, BUFLEN, MSG_CONFIRM);

		//check if it is the end of the integer.
		if(strncmp(buf,"END",3) == 0) {
			//convert int to str  
			sprintf(sumstr,"%d\n",sum);
			//print the message out
			printf("send the sum %s",sumstr);
			//send to client
			send(socketd,sumstr,strlen(sumstr),MSG_CONFIRM);
			//end the loop here
			break;
		}
		//compute the sum
		sum += atoi(buf);
		//print information on console screen
		printf("%s\n",buf);
		printf("%d\n",sum);

	}
	if(n < 0) perror("recv error\n");

}
