
#include <file_allocation_table.h>

#include <read_bootsec.h>
#include <image_access.h>
#include <stdint.h>

int firstFATAdress() {
	return numberBytesPerBlock * numberReservedSectors;
}

long long getFATEntry(int pos) {

	// as 0 and 1 are reserved values only entries >=2 should be requested
	if(pos < 2) return -1;

	int fatSize = numberBytesPerBlock * numberBlocksPerFAT;
	uint8_t fat[fatSize];
	readImage(firstFATAdress(), firstFATAdress() + fatSize , fat);

	long long entry;

	/* from here on fat12 only */

	int mod = pos % 2;
	int index = pos / 2 * 3;

	if(mod) {
		entry = (fat[index + 1] >> 4) + (fat[index + 2] << 4);
	} else {
		entry = ((fat[index + 1] & 0x0F) << 8) + fat[index];
	}

	return entry;
	
	
}
