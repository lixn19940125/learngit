#include <stdio.h>
#include <stdlib.h>

static void exit_1(void){
	printf("my exit_1 \n");
}

int main(int argc, char const *argv[])
{
	if(atexit(exit_1) !=0){
		printf("register error\n");
	}
	return 0;
}