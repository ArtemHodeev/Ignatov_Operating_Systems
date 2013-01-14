/*Связь процессов через pipe(). Сделать связь двух процессов через именованный канал. 
По каналу передаётся структура из 5 строк и 5 значений типа int. второй процесс должен полученные данные распечатать в виде:
Имя: значение.*/
#include <sys/types.h>                                                              
#include <sys/stat.h>                                                                    
#include <fcntl.h>                                                                       
#include <unistd.h>                                                                      
#include <stdio.h>                                                                     
//#define NAME "aaa.fifo""
int main()
{                                                                             
   	int result, i;
	size_t size;   
	char resstring[14];   
	FILE* fd;
	//char name[]="aaa.fifo"; 
   	(void)umask(0);                                                                       
   	mknod("aaa.fifo", S_IFIFO | 0666, 0);                             
    	result = fork();                                                                         
	if (result > 0) 
	{
		fd = fopen("aaa.fifo", "w");
		
		for (i = 0; i < 5; i++)
		{       
			fputs("Hello, world!: ", fd);  
			fprintf(fd, "%d \n",i+1);
		} 
	      	fclose(fd); 
	}                                                          
	else 
	{
		fd = fopen("aaa.fifo", "r");
		char rc;	
		while ((rc = getc (fd)) != EOF)
        		printf("%c" , rc);
 	     	
	      	fclose(fd);  

	}  
                                                                                    
    return 0;                                                                                 
}
