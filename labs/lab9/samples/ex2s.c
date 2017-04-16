// A synchronized client/server message exchange(1 to 1).

// Example 2: Server

#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <time.h>

void child(int sd);

int main(int argc, char *argv[])
{
	int sd, client, portNumber;
	socklen_t len;
	struct sockaddr_in servAdd;

	if(argc != 2)
	{
		printf("Call model: %s <Port #>\n", argv[0]);
		exit(0);
	}

	if ((sd=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		fprintf(stderr, "Cannot create socket\n");
		exit(1);
	}

	servAdd.sin_family = AF_INET;
	servAdd.sin_addr.s_addr = htonl(INADDR_ANY);
	sscanf(argv[1], "%d", &portNumber);
	servAdd.sin_port = htons((uint16_t)portNumber);
	bind(sd,(struct sockaddr*)&servAdd,sizeof(servAdd));
	listen(sd, 5);

	while(1)
	{
		client=accept(sd,(struct sockaddr*)NULL,NULL);
		printf("Got a client\n");
		if(!fork())
			child(client);
		close(client);
	}
}

void child(int sd)
{
	char message[255];
	
	while(1)
	{
		fprintf(stderr, "Enter line to send to client\n");
		fgets(message, 254, stdin);
		write(sd, message, strlen(message)+1);
		if(!read(sd, message, 255))
		{
			close(sd);
			fprintf(stderr,"Bye, client dead, wait for a new client\n");
			exit(0);
		}

		fprintf(stderr, "Client sent back: %s\n", message);
	}
}

