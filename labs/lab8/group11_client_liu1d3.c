        // This is the client
#include <fcntl.h>          
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[])
{
 int fd, fd2;
 char ch;
 char info[100];
 char path[80];
 getcwd(path, 80);
 fd2 = open("log.txt", O_CREAT | O_WRONLY |O_APPEND, 0700 );
 sprintf(info,"PID: %d %s: \n",getpid(),path);
 //printf("this is %s\n",info);
 while((fd=open("/tmp/group11_server", O_WRONLY))==-1){
  fprintf(stderr, "trying to connect\n");
  sleep(1);
 }
 printf("Connected: type in data to be sent\n");
 write(fd, &info, strlen(info));
 while((ch=getchar()) != -1) // -1 is CTR-D
  write(fd, &ch, 1);
 close(fd);
}

