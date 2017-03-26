#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#define SERVER_PORT 5000

int main(int argc, char *argv[]) {
	
	int sock;
	struct sockaddr_in localAddr, srvAddr;
	struct hostent *host;
	//check the arguments of the command.
	if(argc < 2) {
		printf("usage: %s <servername> \n", argv[0]);
	}
	
	host = gethostbyname(argv[1]); 
	if( host == NULL) {
		perror("fail to get host by host name");
		exit(EXIT_FAILURE);
	}
	
	//define socket protocol family 
	srvAddr.sin_family  = AF_INET;
	//copy the the address from hosttoname function
	memcpy((char *)&srvAddr.sin_addr.s_addr, host->h_addr_list[0], host->h_length);
	srvAddr.sin_port = htons(SERVER_PORT);

	//create socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	//check if the socket success or exit for failure
	if( sock < 0 ) {
		perror("fail to open socket!\n");
		exit(EXIT_FAILURE);
	}
	//define socket structure and bind a random local port
	localAddr.sin_family = AF_INET;
	localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	localAddr.sin_port = htons(0);

	if(bind(sock, (struct sockaddr *)&localAddr, sizeof(localAddr)) < 0) {
		perror("fail to bind address");
		exit(EXIT_FAILURE);
	}
	//try to connect to the server
	if(connect(sock, (struct sockaddr *)&srvAddr, sizeof(srvAddr)) < 0) {
		perror("fail to connect remote address");
		exit(EXIT_FAILURE);
	}
	printf("enter integer to send the server\n and press END to finish!\n");
	char buf[100];	
	int i=0;
	while(1) {
		//print the instruction
		printf("The %d integer:",++i);
		//read the input
		scanf("%s",buf);
		//compare the input check if it is the end
		if(strcmp(buf,"END") == 0) {
			//send the end to server
			send(sock,"END\n",5,MSG_CONFIRM);
			//clear buffer
			bzero(buf,100);
			//wait for the recv data
			recv(sock,buf,100,MSG_CONFIRM);
			//print the result
			printf("the sum is %s\n",buf);
			//break the loop
			break;
		}
		//send the integet to server
		send(sock,buf,strlen(buf),MSG_CONFIRM);
   	}
	//close the socket connection
	close(sock);
	printf("Bye!\n");
	exit(EXIT_SUCCESS);
}
