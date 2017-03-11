#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *garv[]) {

	char c;
	FILE *fp;
	if((fp = fopen(argv[1],"r")) == NULL) {
		perror("fail to open %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	char buff[100];
	while(fread(buff, 
}
