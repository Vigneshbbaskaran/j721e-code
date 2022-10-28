#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdint.h>
#include <assert.h>
#include <linux/fs.h>
//#include <linux/major.h>
//#include <linux/mmc/ioctl.h>
#include "mmc.h"

int main(int argc, char **argv )
{
    __u8 buf[512];    
    int ret = 0, fd;
    struct mmc_ioc_cmd ioc;                                    //Basic MMC structure
	
    ioc.opcode = MMC_READ_SINGLE_BLOCK;                       //Command We need to send
	ioc.write_flag = 0;                                        //Read or Write
	ioc.arg = 0x0;                                             //No arg
	ioc.blksz = 512;                                           //Block size
	ioc.blocks = 1;                                            //Number of blocks 
	ioc.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;    //Define more about the commands
    mmc_ioc_cmd_set_data(ioc, buf);

    fd = open(argv[1], O_RDWR);                                 //Open device
    if (fd < 0) {                  
        printf("Failed to open eMMC device, please check which name you have passed\n");
        return 1;
    }
    printf("Device Opened Successfully\n");
    ret = ioctl(fd, MMC_IOC_CMD, &ioc);
    if(ret!=0)
        {
            printf("Ioctl Fails\n");
            return 1; 
        }
    printf("Ioctl Successfully\n");
    printf("Readed data:\n");
    for(int i=0;i<512;i++)
    {
        printf("%d",buf[i]);            
    }
    close(fd);
}


