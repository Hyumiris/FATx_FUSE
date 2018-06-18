#include <stdint.h>

// 0x0B, 2 bytes
// Number of bytes per block/sector in powers of two (almost always 512) 
extern short numberBytesPerBlock;

// 0x0D, 1 byte
// Logical sectors per cluster (allowed values are 1, 2, 4, 8, 16, 32, 64, and 128)
extern uint8_t numberBlocksPerCluster;

// 0x0E, 2 bytes
// Number of reserved logical sectors before the first FAT in the file system image (at least 1 for boot sector)
extern short numberReservedSectors;

// 0x10, 1 byte
// Number of File Allocation Tables (almost always 2)
extern uint8_t numberFATs;

// 0x11, 2 bytes
// Maximum number of FAT12 or FAT16 root directory entries. 0 for FAT32.
extern short numberRootDirectories;

// 0x13, 2 bytes
// Total number of blocks in the entire disk. 
// (If the disk size is larger than 65535 blocks and thus doesn't fit into 2 bytes, this value is set to zero, and the true size is stored at offset 0x20.)
extern short totalNumberBlocks;

// 0x16, 2 bytes
// Logical sectors per File Allocation Table for FAT12/FAT16. 
// (FAT32 sets this to 0 and uses the 32-bit value at offset 0x024 instead.
extern short numberBlocksPerFAT;

int readBootsector(const char* path);

// reads the content of the bootsector to get all the neccessary constant values

