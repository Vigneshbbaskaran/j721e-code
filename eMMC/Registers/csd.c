#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{	
	char buff;
	int fd,i,j;
	fd=open(argv[i],O_RDONLY);
	if(fd<0)
		{
			perror("Open fail");
			_exit(1);
		}
	else
		printf("Open succcess\n");	
	while(1)
	{
		j=read(fd,&buff,1);
		if(j<0)
		{
			perror("Read fails..!!");
			_exit(1);
		}
		else if(j==0)
			break;
		write(1,&buff,1);
	}
	close(fd);
	return 0;
}
