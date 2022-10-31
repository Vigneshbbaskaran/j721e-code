#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int write_device(char *dev)
{
	int fd,ret;
	char buf[]="Vignesh Baskaran";
	fd=open(dev,O_CREAT|O_RDWR|O_TRUNC,0666);	
        if(fd<0)
                {
                        perror("Open fail");
                        _exit(1);
                }
	else
		{
			printf("Open success for write operation\n");
		}	
	ret=write(fd,&buf,17);
	if(ret<=0)
		{
			perror("write fails:\n");
			exit(1);
		}
	else
	{
		printf("Write Success:%d\n",ret);
	}
	close(fd);
	return 0;
}

int read_device(char *dev)
{
	int fd,i,j;
	char buff[4096];
	fd=open(dev,O_RDONLY);
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
		j=read(fd,&buff,4096);
		if(j<0)
		{
			perror("Read fails..!!");
			_exit(1);
		}
		else if(j==0)
			break;
		write(1,&buff,4096);
	}
	close(fd);
	return 0;
}

int main(int argc, char **argv)
{	
	char *device;
	int ret;	

	device = argv[1];
	printf("\ndev name:%s\n",device);
	printf("\ndev name:%s\n",device);

	ret = write_device(device);
	if(ret!=0)
		exit(1);
	
	ret = read_device(device);
	if(ret!=0)
		exit(1);

	printf("\n");
	return 0;
}
