#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PFILE "/tmp/group11server"
#define LOGFILE "group11server_log"

int main(int argc, char *argv[]) {
	int pfd,lfd;
	char ch;

	//check if pipe file exists.
	unlink(PFILE);
	//make pipe file
	if(mkfifo(PFILE, 0777) != 0) {
		printf("fail to create a pipe file in %s",PFILE);
		exit(EXIT_FAILURE);
	}
	//read message from client
	while(1) {
		printf("Waiting for a client\n");
		pfd = open(PFILE, O_RDONLY);
		lfd = open(LOGFILE, O_CREAT | O_WRONLY | O_APPEND, 0777);
		chmod(LOGFILE, 0777);
		if(pfd < 0) {
			printf("fail to create a pipe file: %s\n",PFILE);
			exit(EXIT_FAILURE);
		}	
		if(lfd < 0) {
			printf("fail to create a log file: %s\n",LOGFILE);
			exit(EXIT_FAILURE);
		}	
		printf("new client is accepted\n");
		while(read(pfd, &ch, 1) == 1) {
			printf("%c", ch);
			write(lfd, &ch, 1);
		}
		close(pfd);
		close(lfd);
		
	}
}
