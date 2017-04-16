// A date/time client/server, where the server sends its
// date/time to clients.

// Example 1: Server

#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <time.h>

int main(int argc, char *argv[])
{
	char *myTime;
	time_t currentUnixTime; // time.h
	int sd, client, portNumber;
	socklen_t len;
	struct sockaddr_in servAdd;
	
	if(argc != 2)
	{
		fprintf(stderr,"Call model: %s <Port#>\n",argv[0]);
		exit(0);
	}

/*---- Create the socket. The three arguments are: */
/* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
	if((sd = socket(AF_INET, SOCK_STREAM, 0))<0)
	{
		fprintf(stderr, "Could not create socket\n");
		exit(1);
	}

	servAdd.sin_family = AF_INET;
	servAdd.sin_addr.s_addr = htonl(INADDR_ANY);
	
	sscanf(argv[1], "%d", &portNumber);
	servAdd.sin_port = htons((uint16_t)portNumber);
	
	bind(sd, (struct sockaddr *) &servAdd, sizeof(servAdd));
	listen(sd, 5);

	while(1)
	{
		client=accept(sd,(struct sockaddr*)NULL,NULL);
		printf("Got a date/time request\n");
		currentUnixTime = time(NULL);
		myTime = ctime(&currentUnixTime);
		write(client, myTime, strlen(myTime) + 1);
		close(client);
		printf("Date and Time sent\n");
	}
}
