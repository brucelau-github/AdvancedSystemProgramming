/* 1. The program disables the CTRL-C and CTRL-Z sensitivity. 
 * (be careful if your program hands to do the ps command and kill the process)
 *  2. The program implements the timer alarm.
 *  Logic of the program:
 *  The program will launch a child.
 *  The child will stay alive for a specified number of seconds between 1 and 10 (by a parameter) and then terminates.
 *  The parent will stay alive for a specified number of seconds between 1 and 10 (by parameter) and then terminates.
 *  Each of the child and parent will print a count-down every second to display how many seconds they have to live.
 *  Consider the cases your program should report:
 *  if the child dies before the parent dies: parent declares that the child is dead by displaying a message on the screen
 *  if the child dies after the parent dies: the child declares it is an orphan by displaying a message on the screen
 * Test your code under the two circumstances and use a script file to log and submit your output.
*/
#include <sys/signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
//parent event handler
void pEvent() {
	printf("the parent died or terminated before the child.\n");
}
//child event hander
void cEvent() {
	printf("the child died or terminated before the parent.\n");
}

int main(int argc, char *argv[]) {
	// process the arguments
	if (argc != 3) {
		printf("Arguments error!\n");
		printf("Usage:\n");
		printf("%s [parent TTL] [child TTL]\n",argv[0]);
		exit(-1);
	}

	int pttl,cttl;

	if ( (pttl = atoi(argv[1])) == 0 || (cttl = atoi(argv[2])) == 0 ) {
		printf("Arguments error! TTL should be integer.\n");
		printf("Usage:\n");
		printf("%s [parent TTL] [child TTL]\n",argv[0]);
		exit(-1);
	}

	//process the code

	int status = -1;

	pid_t pid,cpid;
	signal(SIGINT,SIG_IGN);
	signal(SIGTSTP,SIG_IGN);
	//bind child event
	signal(SIGALRM,cEvent);
	printf("keyboard event CTRL-C and CTRL-Z were ignored.\n");
	//fork child
	pid = fork();
	if (pid  == 0) {
		//child process tasks
		//bind parent event
		signal(SIGALRM,pEvent);

		printf("I am the child with pid %d of process id %d\n",getpid(),getppid());
		int n = cttl;

		while(n--) {
			sleep(1);
			printf("child process's time to live in %ds\n",n);
		}
		//send signal to parent before dying and ingnore error.
		//if ( kill(getppid(),SIGALRM) == -1 ) printf("the parent process was dead before the child.\n");
		kill(getppid(),SIGALRM);
		exit(0);

	} else if(pid < 0) {
		printf("Error to fork new child process.\n");
	}

	//parents tasks
	cpid = pid; //get child pid
	printf("I am the parent with pid %d, start to wait the child %d\n",getpid(),cpid);
	waitpid(cpid,&status,1); //no waitnohungup

	int m = pttl;
	while(m--) {
		sleep(1);
		printf("parent process's time to live in %ds.\n",m);
	}
	//send signal to child beofe dying and ignore the error message.
	//if ( kill(cpid,SIGALRM) == -1 ) printf("the child process was dead before the parent\n");
	kill(cpid,SIGALRM);
	exit(0);

}
