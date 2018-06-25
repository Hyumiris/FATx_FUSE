
#include <read_bootsec.h>

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

uint16_t numberBytesPerBlock;
uint8_t numberBlocksPerCluster;
uint16_t numberReservedSectors;
uint8_t numberFATs;
uint16_t numberRootDirectories;
uint16_t totalNumberBlocks;
uint16_t numberBlocksPerFAT;
uint16_t fat_x;

int readBootsector(const char* path)
{
	errno = 0;
	FILE *fp;
    fp = fopen(path, "r");

    if (fp == NULL) {
        printf ("Error opening the image file, errno = %d\n", errno);
        return -1;
    }
 
	unsigned char c;	
 	int b_count = 0x00; 	   
 	numberBytesPerBlock = 0;
 	numberReservedSectors = 0;
 	numberRootDirectories = 0;
 	totalNumberBlocks = 0;
 	numberBlocksPerFAT = 0;
 	fat_x = 0;

    while(b_count <= 0x3A) 
    {
    	c = fgetc(fp);

    	if (b_count == 0x0B) 
    	{
    		numberBytesPerBlock += c;
    	} 
    	else if (b_count == 0x0C) 
    	{
    		numberBytesPerBlock += c << 8;
    	}
    	else if (b_count == 0x0D) 
    	{
    		numberBlocksPerCluster = c;
    	} 
    	else if (b_count == 0x0E) 
    	{
    		numberReservedSectors += c;
    	}
    	else if (b_count == 0x0F)
    	{
    		numberReservedSectors += c << 8;	
    	}
    	else if (b_count == 0x10)
    	{
    		numberFATs = c;
    	}
    	else if (b_count == 0x11)
    	{
    		numberRootDirectories += c;
    	}
    	else if (b_count == 0x12)
    	{
    		numberRootDirectories += c << 8;
    	}
    	else if (b_count == 0x13)
    	{
    		totalNumberBlocks += c;
    	}
    	else if (b_count == 0x14)
    	{
    		totalNumberBlocks += c << 8;	
    	}
    	else if (b_count == 0x16)
    	{
    		numberBlocksPerFAT += c;
    	}
    	else if (b_count == 0x17)
    	{
    		numberBlocksPerFAT += c << 8;	
    	}
    	else if (b_count == 0x39)
    	{
    		fat_x += (c - 48) * 10;
    	}
    	else if (b_count == 0x3A)
    	{
    		fat_x += c - 48;
    	}

    	b_count += 1;
    }

    fclose (fp);

	return 0;
}