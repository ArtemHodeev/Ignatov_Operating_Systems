/*Задача producer-consumer. 2 процесса имеют общий буфер, реализованный через разделяемую память. Использовать System V семафоры.*/
#include <stdio.h>	 
#include <stdlib.h>     
#include <sys/types.h>  
#include <sys/ipc.h>     
#include <sys/sem.h>

int main()
{
    int sem_set_id;	     
    int pid;	     
    int i;		    
    struct sembuf sem_op;
	if((sem_set_id = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT)) < 0)
	{
        printf("Can\'t get semid\n");
        exit(-1);
    }
	pid = fork();
    switch (pid) 
	{
	case -1:    
		exit(1);
	case 0:	
		for (i=0; i<15; i++) 
		{
			sem_op.sem_num = 0;
			sem_op.sem_op = -1;
			sem_op.sem_flg = 0;
			semop(sem_set_id, &sem_op, 1);
			printf("consumer: '%d'\n", i);
	    }
	    break;
	default:
	    for (i=0; i<15; i++) 
		{
			printf("producer: '%d'\n", i);
			sem_op.sem_num = 0;
			sem_op.sem_op = 1;
			sem_op.sem_flg = 0;
			semop(sem_set_id, &sem_op, 1);
	    }
	    break;
    }
    return 0;
}
