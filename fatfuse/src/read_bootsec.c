
#include <read_bootsec.h>

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

short numberBytesPerBlock;
uint8_t numberBlocksPerCluster;
short numberReservedSectors;
uint8_t numberFATs;
short numberRootDirectories;
short totalNumberBlocks;
short numberBlocksPerFAT;

int readBootsector(const char* path)
{
	FILE *fp;
    fp = fopen(path, "r");

    if (fp == NULL) {
        printf ("Error opening the image file, errno = %d\n", errno);
        return -1;
    }
 
	char c;	
 	int b_count = 0x00; 	   
 	numberBytesPerBlock = 0;
 	numberReservedSectors = 0;
 	numberRootDirectories = 0;
 	totalNumberBlocks = 0;
 	numberBlocksPerFAT = 0;

    while((c = fgetc(fp)) != 0) 
    {
    	if (b_count == 0x0B) 
    	{
    		numberBytesPerBlock += c << sizeof(uint8_t);
    	} 
    	else if (b_count == 0x0C) 
    	{
    		numberBytesPerBlock += c;
    	}
    	else if (b_count == 0x0D) 
    	{
    		numberBlocksPerCluster = c;
    	} 
    	else if (b_count == 0x0E) 
    	{
    		numberReservedSectors += c << sizeof(uint8_t);
    	}
    	else if (b_count == 0x0F)
    	{
    		numberReservedSectors += c;	
    	}
    	else if (b_count == 0x10)
    	{
    		numberFATs = c;
    	}
    	else if (b_count == 0x11)
    	{
    		numberRootDirectories += c << sizeof(uint8_t);
    	}
    	else if (b_count == 0x12)
    	{
    		numberRootDirectories += c;
    	}
    	else if (b_count == 0x13)
    	{
    		totalNumberBlocks += c << sizeof(uint8_t);
    	}
    	else if (b_count == 0x14)
    	{
    		totalNumberBlocks += c;	
    	}
    	else if (b_count == 0x16)
    	{
    		numberBlocksPerFAT += c << sizeof(uint8_t);
    	}
    	else if (b_count == 0x17)
    	{
    		numberBlocksPerFAT += c;	
    	}
    }

    fclose (fp);

	return 0;
}