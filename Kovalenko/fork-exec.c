/*������� fork()/exec(). �������� 2 ���������. ������ ������ ��������� 5 ����� ������.*/
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int i = 0;
	pid_t pid;

    for (i = 0; i < 5; i++)
    {
        printf("%d\n", i);
		pid = fork();
		if (pid == 0)
		{
			execl("./hello", "/home/anast/ddd/hello", NULL, NULL);
			//execl("/bin/ls", "/bin/ls", "-r", "-t", "-l", (char *) 0); //����� ��������� ��� ���������
		}
		else if (pid < 0) _exit(1);
    }
    while(1);

    /*return 0;*/
}
