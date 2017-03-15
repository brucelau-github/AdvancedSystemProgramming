#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PFILE "/tmp/group11_server"

int main(int argc, char *argv[]) {
	int fd;
	char ch;
	while((fd=open(PFILE,O_WRONLY))==-1){
		fprintf(stderr, "trying to connect the server\n");
		sleep(1);
	}

	printf("Connected: type your full name and student id to be sent\n");
	char head[100];
	sprintf(head, "%d", getpid());
	strcat(head, " ");
	getcwd(head + strlen(head));
	strcat(head, " ");
	fgets(head + strlen(head), 100, stdin);
	strcat(head, "\n");
	printf("%s\n",head);
	write(fd, head, strlen(head) + 1);
	close(fd);
}
