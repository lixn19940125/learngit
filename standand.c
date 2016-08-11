#include <stdio.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
	int c;

	while((c = getc(stdin)) != EOF)
		if(putc(c,stdout) == EOF)
			printf("out error\n");


	if(ferror(stdin)){
		printf("stdin error\n");
	}

	exit(0);
}
