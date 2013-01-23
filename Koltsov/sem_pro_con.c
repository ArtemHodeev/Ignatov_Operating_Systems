#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main()
{
    int sem_id;	
    int pid;	
    int i;	
    struct sembuf sem_op;

    char pathname[] = "sem_pro_con.c"; // file name intended for key generation
	key_t key; // IPC key

//================== CREATE SEMAPHORE ===============================

	if((key = ftok(pathname,0)) < 0)
	{
		printf("Can not generate key\n");
		exit(-1);
	}


	sem_id = semget( key , 1 , 0666 | IPC_CREAT );

	if( sem_id < 0 )
	{
        printf("Can\'t get semid\n");
        exit(-1);
	}
	

//=================== CREATING PROCESS ==============================

	pid = fork();    
	
	if ( pid == 0) 							// child ( consumer )
	{

		for (i=0; i<15; i++)
		{
			sem_op.sem_num = 0;
			sem_op.sem_op = -1;
			sem_op.sem_flg = 0;
			semop ( sem_id, &sem_op, 1  );
			printf( "Consumer: ' %d '\n", i );
		}
	}
	

	else 									// parent ( producer )
	{

		for (i=0; i<15; i++)
		{
			printf( "Producer: ' %d '\n", i );
			sem_op.sem_num = 0;
			sem_op.sem_op = 1;
			sem_op.sem_flg = 0;
			semop ( sem_id, &sem_op, 1  );
		}
	}
	
	return 0;
}