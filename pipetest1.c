#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#define DEF_PAGER "/usr/bin/more"
#define MAXLINE 10000
int main(int argc, char const *argv[])
{
	int n,fd[2];
	pid_t pid;
	char line[MAXLINE],*pager,*argv0;
	FILE *fp;

	if(argc != 2){
		printf("usage : a.out <pathname>\n");
	}
	if((fp = fopen(argv[1],"r")) == NULL){
		printf("can't open %s\n",argv[1]);
	}
	if(pipe(fd)<0)
		printf("pipe error\n");

	if((pid = fork()) < 0){
		printf("fork error\n");
	}else if(pid > 0){
		close(fd[0]);//close read

		while(fgets(line,MAXLINE,fp) != NULL){
			n = strlen(line);
			if(write(fd[1],line,n) != n)
				printf("write error to pipe\n");
		}

		if(ferror(fp))
			printf("fgets error\n");

		close(fd[1]);

		if(waitpid(pid,NULL,0) < 0)
			printf("waitpid error\n");

		exit(0);
	}else{
		close(fd[1]);
		if(fd[0] != STDIN_FILENO){
			if(dup2(fd[0],STDIN_FILENO) != STDIN_FILENO){
				printf("dup2 error to stdin\n");
			}
			close(fd[0]);
		}

		if((pager = getenv("PAGER")) == NULL)
			pager = DEF_PAGER;
		if((argv0 = strrchr(pager,'/')) != NULL)
			argv0++;
		else
			argv0 = pager;

		if(execl(pager,argv0,(char*)0)<0)
			printf("execl error for %s\n",pager);
	}
	return 0;
}