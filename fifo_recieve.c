#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void read_fifo(int descriptor)
{
	char message[100]="";
	if(read(descriptor,message,sizeof(message))<0)
		perror("read");
	printf("Odebrana wiadmosc: %s", message);
}

int main(void)
{
	if(mkfifo("fifo",0600)<0)
		perror("read");
	int descriptor = open ("fifo",O_RDONLY);
	if(descriptor < 0)
		perror("open");
	read_fifo(descriptor);
	if(close(descriptor)<0)
		perror("close");
	if(unlink("fifo")<0)
		perror("unlink");
	return 0;
}
