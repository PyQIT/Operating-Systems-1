#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

struct msgbuf{
	long type;
	char mtext[50];
};

void receive_message(int mqid)
{
	struct msgbuf buffer;

	if(msgrcv(mqid,&buffer,sizeof(buffer.mtext),1,0)<0)
		perror("msgrcv");
	else
		printf("Odebrany komunikat: %s\n",buffer.mtext);
}

int main(void)
{
	int key = ftok("/tmp",8);
	if(key < 0)
		perror("ftok");
	
	int id = msgget(key, 0600 | IPC_CREAT | IPC_EXCL);
	if(id<0)
		perror("msgget");

	receive_message(id);

	if(msgctl(id,IPC_RMID,0)<0)
		perror("msgctl");

	return 0;
}
