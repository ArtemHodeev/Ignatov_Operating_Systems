/*���������� pthread. �������������� ��������� lab04/create.c, ���������� �������� �������� �����������.*/
#include <stdio.h>
#include <pthread.h> 
int turn = 0;
main()
{
    pthread_t f2_thread, f1_thread;
    void *f2(), *f1();
    int i1,i2;
	
    i1 = 1;
    i2 = 2;
	
	pthread_create(&f1_thread,NULL,f1,&i1);
    pthread_create(&f2_thread,NULL,f2,&i2);

    pthread_join(f1_thread,NULL);
    pthread_join(f2_thread,NULL);
}

void *f1(int *x)
{
    int i, k;
    i = *x;
	for (k = 0; k < 20; k++)
	{
		while (turn != 0);
		sleep(1);
		printf("f1: %d\n",i++);
		turn = 1;
	}
    pthread_exit(0); 
}

void *f2(int *x)
{
    int i, k;
    i = *x;
    for (k = 0; k < 20; k++)
	{
		while (turn != 1);
		sleep(1);
		printf("f2: %d\n",i++);
		turn = 0;
	}
	pthread_exit(0); 
}