#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]){
 int fd;
 char ch;
 char pid [10];
 char pn [30]; 
 char blank = ' ';
while ((fd = open ("/tmp/group11_server",O_WRONLY)) == -1){
  fprintf(stderr, "trying to connect\n");
  sleep(1);
 }
 printf("Connected: type in data to be sent\n"); 
 sprintf(pid,"%d",getpid());
 getcwd(pn, sizeof(pn));
 write(fd, pn, strlen(pn));
 write(fd, &blank,1);
 write(fd,pid,strlen(pid));
 write(fd, &blank,1);
 while((ch = getchar())!= -1){
  write(fd,&ch,1);
  
 }
 close(fd);
}
