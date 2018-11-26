#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

void down(int semset_id)
{
	struct sembuf down_operation = {0,-1,0};

	if(semop(semset_id,&down_operation,1)<0)
		perror("semop");
}

int main(void)
{
	int key = ftok("/tmp",8);
	if(key < 0)
		perror("ftok");
	int semset_id = semget(key,1,0600);
	if(semset_id < 0)
		perror("semget");
	down(semset_id);
	return 0;
}
