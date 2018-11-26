#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

enum pipe_descriptors {READ, WRITE};

void parent_work(int descriptors[])
{
	char message[100] = "";
	if(close(descriptors[WRITE])<0)
		perror("parent - close write");
	if(read(descriptors[READ],message,sizeof(message))<0)
		perror("read");
	printf("Odebrana wiadomosc: %s\n",message);
	if(close(descriptors[READ])<0)
		perror("parent - close read");
	if(wait(0)<0)
		perror("wait");
}

void child_work (int descriptors[])
{
	char *message = "Kolokwium na 30 pkt";
	
	if(close(descriptors[READ])<0)
		perror("parent - close read");
	if(write(descriptors[WRITE],message,strlen(message))<0)
		perror("write");
	if(close(descriptors[WRITE])<0)
		perror("parent - close write");
	exit(0);
}

int main(void)
{
	int descriptors[2];
	if(pipe(descriptors)<0)
		perror("pipe");
	int pid = fork();
	if(pid == -1)
		perror("fork");
	if(pid == 0)
		child_work(descriptors);
	else
		parent_work(descriptors);
	return 0;
}
