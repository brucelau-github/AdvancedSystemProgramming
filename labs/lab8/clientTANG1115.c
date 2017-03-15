#include <fcntl.h> // This is the client
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
	//declaration 
    int fd;
    char ch;
    char pid [10];
    char cwd [30]; 
    char space = ' ';
   
    // connect to the server of the group11 
    while ((fd = open ("/tmp/group11_server",O_WRONLY)) == -1){
    	fprintf(stderr, "trying to connect\n");
        sleep(1);
    }
    
    // get PID, CWD, Last Name, First Name, UWinID
    printf("Connected: type in data to be sent\n"); 
    sprintf(pid,"%d",getpid());
    getcwd(cwd, sizeof(cwd));
    write(fd, cwd, strlen(cwd));
    write(fd, &space,1);
    write(fd,pid,strlen(pid));
    write(fd, &space,1);
    
    // get char
    while((ch = getchar())!= -1){ //-1 is CTR-D
    	write(fd,&ch,1);
    }
    close(fd);
}
