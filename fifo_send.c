#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

void write_fifo(int descriptor)
{
	char *message = "Kolokwium na 30 pkt";
	if(write(descriptor,message,strlen(message))<0)
		perror("write");
}

int main(void)
{
	int descriptor = open("fifo",O_WRONLY);
	if(descriptor < 0)
		perror("open");
	write_fifo(descriptor);
	if(close(descriptor)<0)
		perror("close");
	return 0;
}
