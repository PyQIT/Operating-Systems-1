#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

struct msgbuf {
	long type;
	char mtext[20];
};

void receive_message(int mqid)
{
	struct msgbuf buffer;

	if(msgrcv(mqid,&buffer,sizeof(buffer.mtext),1,0)<0)
		perror("msgrcv");
	else
		printf("Odebrany komunikat: %s\n",buffer.mtext);
}

void send_message(int mqid, char message[])
{
	struct msgbuf buffer;

	buffer.type = 1;
	strncpy(buffer.mtext,message,20-1);

	if(msgsnd(mqid,&buffer,sizeof(buffer.mtext),0)<0)
		perror("msgsnd");
}

int main(void)
{
	int key = ftok("/tmp",8);
	if(key<0)
		perror("ftok");

	int id = msgget(IPC_PRIVATE, 0600 | IPC_CREAT | IPC_EXCL);
	if(id < 0)
		perror("msgget");

	send_message(id,"Systemy oper");

	receive_message(id);

	if(msgctl(id,IPC_RMID,0)<0)
		perror("msgctl");

	return 0;
}
