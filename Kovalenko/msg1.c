/*Задача producer-consumer. 2 процесса имеют общий буфер, реализованный через разделяемую память. Использовать System V сообщения*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>

#define LAST_MESSAGE 255 /* Тип сообщения для прекращения работы */

typedef struct mesg {
	long type; /* must be positive */
	char data[81];
} Mesg;

Mesg mesg;

int main(void)
{
	int  i, pid, maxlen;
	char pathname[] = "msg1.c"; /* Имя файла, использующееся для генерации ключа.
	Файл с таким именем должен существовать в текущей директории */

    	key_t key; /* IPC ключ */
	
	size_t len = 0;
	
	int msqid; /* IPC дескриптор для очереди сообщений */

	if((key = ftok(pathname,0)) < 0)
	    {
			printf("Can\'t generate key\n");
			exit(-1);
	    }
        /*
	 создаем очередь сообщений
	 */
	msqid = msgget(key, 0666 | IPC_CREAT);
	if (msqid < 0) 
	{
		perror("cannot make message queue");
		_exit(-1);
	}
	printf("создали очередь сообщений\n");
	/*создаем процессы*/
	pid = fork();
	if (pid < 0) 
	{
		perror("cannot fork");
		_exit(-1);
	}
	if (pid == 0) /* ребенок -консьюмер */
	{	
		printf("consumer:  получаю сообщения....\n");
		for (i = 1; i < 15; i++) 
		{
			maxlen = msgrcv(msqid, &mesg, sizeof(Mesg), 0);
			if (maxlen <= 0 || mesg.type == LAST_MESSAGE) break;
			printf("consumer:message type:%ld, data:%s, %d\n", mesg.type, mesg.data, i);
		}
		/* Если принятое сообщение имеет тип LAST_MESSAGE, прекращаем работу и удаляем очередь сообщений из системы.
				В противном случае печатаем текст принятого сообщения. */

		if (mesg.type == LAST_MESSAGE)
			printf("consumer: УРРРА!!!!!\n");
	
	} 
	else /* родитель - продюсер */
	{	

		printf("producer: отправляю сообщения....\n");
		/* Сначала заполняем структуру для нашего сообщения и определяем длину информативной части */
		for (i = 1; i < 15; i++) 
		{
			mesg.type = 1;
			strcpy(mesg.data, "This is text message");
			printf("producer:message type:%ld, data:%s, %d\n", mesg.type, mesg.data, i);
			len = strlen(mesg.data)+17;
			msgsnd(msqid, &mesg, len, 0);
		}
		/* Отсылаем сообщение, которое заставит получающий процесс прекратить работу, с типом LAST_MESSAGE и длиной 0 */
		printf("producer: send LAST_MESSAGE\n");
		mesg.type = LAST_MESSAGE;
		msgsnd(msqid, &mesg, sizeof(mesg.type), 0);
		printf("producer: УРРРА!!!!!\n");
		wait(NULL);
	}
return 0;
	
}
