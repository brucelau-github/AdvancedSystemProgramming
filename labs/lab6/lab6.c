#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Execute the command using this shell program.  */
#define SHELL "/bin/bash"
int run_cmd(char cmd[]);
void assemble_args(int cmdlen, char *buff, char *cmd);

int run_cmd(char cmd[]) {
  int status;
  pid_t pid;
  pid = fork ();
  if (pid == 0)
  {
    execl (SHELL, SHELL, "-c", cmd, NULL);
    _exit (EXIT_FAILURE);
  }
  else if (pid < 0) {
    perror("error to allocate resource!");
    status = -1;
  }
  else
  /* This is the parent process.  Wait for the child to complete.  */
  if (waitpid (pid, &status, 0) != pid)
      status = -1;
  return status;
}
void assemble_args(int cmdlen, char *buff, char *cmd) {
  int i;
  bzero(cmd,100); //reset cmd;
  for(i=0; i<cmdlen; i++) {
    *(cmd+i) = *(buff+i);
  }
  *(cmd+cmdlen)='\0';
}
int main(int argv, char *args[])
{
  int cmdlen;
  char cmd[100];
  char ps1[]="Enter a command :";
  pid_t pid;
  char buffer[100];
  printf("press exit to quit this program.\n");
  while (1) {
    write(0, ps1, strlen(ps1));
    cmdlen = read(0,buffer,100);
    assemble_args(cmdlen, buffer, cmd);
    if(strncasecmp(cmd,"exit",4) == 0) break;
    if(cmdlen > 1)
      run_cmd(cmd);
  }

  return 0;
}
