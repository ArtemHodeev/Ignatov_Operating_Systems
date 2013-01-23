#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>

#define STOP_MSGS 255 

struct mymsgbuf {
long type;
char data[81];
} mybuf;


int main(void)
{

	int i, pid, maxlen;
	char pathname[] = "mesg_pro_con.c"; // file name intended for key generation
	key_t key; // IPC key
	size_t len = 0;
	int msqid; // IPC message queue descriptor

	//============================ CREATING MSG QUEUE ==========================================


	if((key = ftok(pathname,0)) < 0)
	{
		printf("Can not generate key\n");
		exit(-1);
	}


	msqid = msgget(key, 0666 | IPC_CREAT);

	if (msqid < 0)
	{
		perror("Can not make message queue\n");
		_exit(-1);
	}
	
	printf("Message queue was made\n");

	

	//============================== CREATING PROCESSES =========================================
	
	pid = fork();
	
	if ( pid == 0 ) 		//child ( consumer )
	{	

		printf("Consumer: getting messages....\n");
		for (i = 1; i < 15; i++)
		{
			maxlen = msgrcv( msqid, &mybuf, sizeof(mymsgbuf), 0 );
			if ( maxlen <= 0 || mybuf.type == STOP_MSGS ) break;
			printf ( "Consumer: message type: %ld, data: %s , %d\n", mybuf.type, mybuf.data, i );
		}

		if (mybuf.type == STOP_MSGS) printf("Consumer: FINISH \n");
	}
	




	else 					// parent ( producer )
	{	

		printf("Producer: sending messages....\n");
		for (i = 1; i < 15; i++)
		{
			mybuf.type = 1;
			strcpy(mybuf.data, "This is a text message");
			printf("Producer: message type: %ld, data: %s , %d\n", mybuf.type, mybuf.data, i);
			len = strlen(mybuf.data)+17;
			msgsnd(msqid, &mybuf, len, 0);
		}

		printf("Producer: send STOP_MSGS\n");
		mybuf.type = STOP_MSGS;
		msgsnd(msqid, &mybuf, sizeof(mybuf.type), 0);
		printf("Producer: FINISH \n");
		wait(NULL);
	}


	return 0;
}