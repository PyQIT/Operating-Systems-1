#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

void up_wait(int semset_id)
{
	struct sembuf up_operation = {0,1,0};
	struct sembuf wait_operation = {0,0,0};
	char error_message[15];

	if(semop(semset_id,&up_operation,1)<0)
	{
		sprintf(error_message,"semop %u",__LINE__-1);
		perror(error_message);
	}

	if(semop(semset_id,&wait_operation,1)<0)
	{
		sprintf(error_message,"semop %u",__LINE__-1);
		perror(error_message);
	}
}

int main(void)
{
	int key = ftok("/tmp",8);
	if(key < 0)
		perror("ftok");
	int semset_id = semget(key,1,0600|IPC_CREAT|IPC_EXCL);
	if(semset_id < 0)
		perror("semget");
	up_wait(semset_id);
	if(semctl(semset_id,0,IPC_RMID)<0)
		perror("semctl");

	return 0;
}
