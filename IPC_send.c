#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

struct msgbuf {
	long type;
	char mtext[50];
};

void send_message(int mqid, char message[])
{
	struct msgbuf buffer;

	buffer.type = 1;
	memset(buffer.mtext,0,sizeof(buffer.mtext));
	strncpy(buffer.mtext,message,50-1);

	if(msgsnd(mqid,&buffer,sizeof(buffer.mtext),0)<0)
		perror("msgsnd");
}

int main(void)
{
	int key = ftok("/tmp",8);
	if(key<0)
		perror("ftok");

	int id = msgget(key,0600);
	if(id < 0)
		perror("msgget");

	send_message(id,"Systemy operacyjne");

	return 0;
}
