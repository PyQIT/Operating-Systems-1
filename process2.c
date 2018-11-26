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

void create_children(void)
{
	int i;
	for(i = 0; i< 5; i++){
		int pid = fork();
		printf("%d\n",getpid());

		if(pid<0)
			perror("fork");
		if(pid == 0)
			do_child_work();
	}
}

void wait_children(void)
{
	int i;
	for(i = 0; i<5; i++)
		do_parent_work();
}

int main(void)
{
	create_children();
	wait_children();
	
	return 0;
}
