#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MAXX 20

int main(int argc, char const *argv[])
{
	pid_t pd;
	int n, fd[2];
	char line[MAXX];

	if(pipe(fd)<0)
		printf("pipe error\n");

	if((pd = fork()) < 0){
		printf("fork error\n");
	}else if(pd > 0){
		close(fd[0]);
		write(fd[1],"hello,world!",12);
	}else if(pd == 0){
		close(fd[1]);
		n = read(fd[0],line,MAXX);
		write(STDOUT_FILENO,line,n);
	}
	exit(0);
}					