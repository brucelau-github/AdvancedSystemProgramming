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
	
	int sock, rc, i;
	struct sockaddr_in localAddr, srvAddr;
	struct hostent *host;

	if(argc < 3) {
		printf("usage: %s <servername> <data> \n", argv[0]);
	}
	
	host = gethostbyname(argv[1]); 
	if( host == NULL) {
		perror("fail to get host by host name");
		exit(EXIT_FAILURE);
	}

	srvAddr.sin_family  = AF_INET;
	memcpy((char *)&srvAddr.sin_addr.s_addr, host->h_addr_list[0], host->h_length);
	srvAddr.sin_port = htons(SERVER_PORT);

	//create socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if( sock < 0 ) {
		perror("fail to open socket!\n");
		exit(EXIT_FAILURE);
	}
	//bind local port
	localAddr.sin_family = AF_INET;
	localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	localAddr.sin_port = htons(0);

	if(bind(sock, (struct sockaddr *)&localAddr, sizeof(localAddr)) < 0) {
		perror("fail to bind address");
		exit(EXIT_FAILURE);
	}
	if(connect(sock, (struct sockaddr *)&srvAddr, sizeof(srvAddr)) < 0) {
		perror("fail to connect remote address");
		exit(EXIT_FAILURE);
	}
	//open a file
	FILE *imgfd;
	struct stat *imgstat;
	imgfd = fopen(argv[2], "r");
	int imgfsize;
	stat(argv[2], imgstat);
	imgfsize = imgstat->st_size;
	printf("sending picture size:%d\n", imgfsize);
//	write(sock, &imgfsize, sizeof(imgfsize));

	char imgbuffer[200];
	while(!feof(imgfd)) {
		fread(imgbuffer, sizeof(imgbuffer), 1, imgfd);
		write(sock, imgbuffer, sizeof(imgbuffer));
		bzero(imgbuffer,sizeof(imgbuffer));
   	}
	printf("finished!\n waiting for feedback\n");
	char sockbuf[500];
	read(sock, sockbuf, sizeof(sockbuf));
	printf("the result is %s",sockbuf);
	fclose(imgfd);
	close(sock);
}
