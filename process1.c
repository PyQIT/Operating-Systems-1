#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void do_child_work(void)
{
	puts("\nJestem dzieciakiem");
	exit(0);
}

void do_parent_work(void)
{
	puts("\nJestem rodzicem");
	if(wait(0)<0)
		perror("wait");
}

int main(void)
{
	int pid = fork();
	printf("%d",getpid());

	if(pid<0)
		perror("fork");
	if(pid == 0)
		do_child_work();
	else
		do_parent_work();
	return 0;
}
