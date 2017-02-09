#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
int isvowels(int c);
int isvowels(int c) {
	return c == 'a' || c == 'e' || c=='o' || c=='u' || c=='i';
}
int main(int argc, char *argv[])
{
	int fd1, fd2;
	char buffer[100];
	long int n1;
	int n_digits=0,
		n_characters=0,
		n_spaces=0,
		n_punctulation=0,
		n_vowels=0,
		n_cases=0;

	if(((fd1 = open(argv[1], O_RDONLY)) == -1) ||
	  ((fd2 = open(argv[2], O_CREAT|O_WRONLY|O_TRUNC,0700)) == -1))
	{
		perror("file problem ");
		exit(1);
	}

	while((n1=read(fd1, buffer, 100)) > 0)
  {
    //read characters
    int lenOfBuffer = strlen(buffer);
    char *c=buffer;
    int i = 0;
    while( c < (buffer+n1) ) {
      if(isdigit(*c)) {
        n_digits++;
      }
			if (ispunct(*c)) {
				n_punctulation++;
			}
			if (isspace(*c)) {
				n_spaces++;
			}
			if (isalpha(*c)) {
				n_characters++;
				if(isvowels(*c)) {
					n_vowels++;
				}
				if(islower(*c)) {
					n_cases++;
					*c = toupper(*c);
				}
			}
			c++;
    }
    if(write(fd2, buffer, n1) != n1)
    {
      perror("writing problem ");
      exit(3);
    }

  }
	// Case of an error exit from the loop
	if(n1 == -1)
	{
		perror("Reading problem ");
		exit(2);
	}

	close(fd1);
	close(fd2);
	printf("Number of spaces: %d\n", n_spaces);
	printf("Number of characters: %d\n", n_characters);
	printf("Number of vowels: %d\n", n_vowels);
	printf("Number of digits: %d\n", n_digits);
	printf("Number of punctuations: %d\n", n_punctulation);
	printf("Converted: %d cases\n", n_cases);
	exit(0);
}
