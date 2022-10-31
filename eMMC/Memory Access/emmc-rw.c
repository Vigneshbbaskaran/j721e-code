#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{	
	char buff[20];
	int fd,i,j;
	char buf[]="Vignesh Baskaran";
	printf("\ndev name:%s\n",argv[1]);
	fd=open(argv[1],O_CREAT|O_RDWR|O_TRUNC,0666);	
        if(fd<0)
                {
                        perror("Open fail");
                        _exit(1);
                }
	else
		{
			printf("Open success for write operation\n");
		}	
	j=write(fd,&buf,20);
	if(j<=0)
		{
			perror("write fails:\n");
			exit(1);
		}
	else
	{
		printf("Write Success:%d\n",j);
	}
	close(fd);
	fd=open(argv[1],O_RDONLY);
	if(fd<0)
		{
			perror("Open fail");
			_exit(1);
		}
	else
		printf("Open succcess for read\n");	
	j=0;
	for(i=0;i<4;i++)
	{
	//	printf("\n");
		j=read(fd,&buff,5);
		if(j<0)
		{
			perror("Read fails..!!");
			_exit(1);
		}
		else if(j==0)
			break;
		//printf("%d.data:\n",i);
		write(1,&buff,5);
	}
	close(fd);
	printf("\n");
	return 0;
}
