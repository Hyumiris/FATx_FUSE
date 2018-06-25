#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	// Create filepointer
	FILE *fp;

	// open file
	fp = fopen("VirtualDisk.img", "wb");

	if(fp == NULL) {
		printf("Datei konnte NICHT geoeffnet werden.\n");
	}else {
		printf("Datei konnte geoeffnet werden.\n");
	}

	//fprintf (fp, "3");
	//char JmpBoot[] = {0xEB, 0x3C, 0x90};

	char JmpBoot[] = {0xeb, 0x3c, 0x90};
	fwrite(JmpBoot, 3, 1, fp);

	char OSName[] = "HPI_BS_2";
	fwrite(OSName, 8, 1, fp);

	char BytesPerSec[] = {0x00, 0x02};
	fwrite(BytesPerSec, 2, 1, fp);

	char SecPerClus[] = {0x01};
        fwrite(SecPerClus, 1, 1, fp);

	char RsvdSecCnt[] = {0x01, 0x00};
        fwrite(RsvdSecCnt, 2, 1, fp);

	char NumFATs[] = {0x01};
        fwrite(NumFATs, 1, 1, fp);

	char Rest[] =  {0xe0, 0x00, //RootEntCnt
		        0x40, 0x0b, //TotSec
		        0xf0,	    //MediaType
		        0x09, 0x00, //FATSize
		        0x12, 0x00, //SecPerTrack
			0x02, 0x00, //NumHeads
			0x00, 0x00, 0x00, 0x00, //HiddenSec
			0x00, 0x00, 0x00, 0x00, //TotSec32
			0x00,       //DrvNum
			0x00,       //Reserved
			0x29};      //

	fwrite(Rest, 22, 1, fp);

	char Rest2[] =	{"HPI!BesteGruppeFAT12   "};
        fwrite(Rest2, 23, 1, fp);

	char Null[] = {0x00};
	for (int i = 0; i < 448; i++) {
		fwrite(Null, 1,1,fp);
	}

	char Ende[] = {0x55, 0xaa};
	fwrite(Ende, 2,1,fp);

	for (int i = 0; i < 9 * 512; i++) {
		fwrite(Null, 1,1,fp);
	}

	char nameDevice[] = {"BesteGruppe"};
	fwrite(nameDevice, 11,1,fp);

	char komischesFlag[] = {0x28};
	fwrite(komischesFlag, 1,1,fp);

	for (int i=0; i < 10; i++) {
		fwrite(Null,1,1,fp);
	}

	char date[] = {0x91, 0x9e, 0x65, 0x39};
	fwrite(date, 4,1,fp);

	for (int i=0; i < 6; i++) {
                fwrite(Null,1,1,fp);
        }

	for (int i=0; i < 30 * 16; i++) {
                fwrite(Null,1,1,fp);
        }

	for (int i=0; i < 2869 * 512; i++) {
                fwrite(Null,1,1,fp);
        }


	fclose (fp);
	return 0;
}
