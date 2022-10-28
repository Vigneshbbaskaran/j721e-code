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

/*struct mmc_ioc_cmd {
	/*
	 * Direction of data: nonzero = write, zero = read.
	 * Bit 31 selects 'Reliable Write' for RPMB.
	 */
//	int write_flag;

	/* Application-specific command.  true = precede with CMD55 */
/* 	int is_acmd;

	__u32 opcode;
	__u32 arg;
	__u32 response[4]; */  /* CMD response */
/* 	unsigned int flags;
	unsigned int blksz;
	unsigned int blocks;
*/
	/*
	 * Sleep at least postsleep_min_us useconds, and at most
	 * postsleep_max_us useconds *after* issuing command.  Needed for
	 * some read commands for which cards have no other way of indicating
	 * they're ready for the next command (i.e. there is no equivalent of
	 * a "busy" indicator for read operations).
	 */
/* 	unsigned int postsleep_min_us;
	unsigned int postsleep_max_us;
 */
	/*
	 * Override driver-computed timeouts.  Note the difference in units!
	 */
/* 	unsigned int data_timeout_ns;
	unsigned int cmd_timeout_ms;
 */
	/*
	 * For 64-bit machines, the next member, ``__u64 data_ptr``, wants to
	 * be 8-byte aligned.  Make sure this struct is the same size when
	 * built for 32-bit.
	 */
/* 	__u32 __pad;
 */
	/* DAT buffer */
/* 	__u64 data_ptr;
};
 */





int main(int argc, char **argv )
{
    __u8 buf[512];    
    int ret = 0, fd;
    struct mmc_ioc_cmd ioc;
	
    ioc.opcode = MMC_READ_MULTIPLE_BLOCK;                      //Command We need to send
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
    
    ret = ioctl(fd, MMC_IOC_CMD, &ioc);
    printf("Readed data:\n");
    for(int i=0;i<512;i++)
    {
        printf("%d",buf[i]);            
    }
    close(fd);
}


