
#include <image_access.h>

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char* sourcefile;
FILE* fd;

int openFileDescriptor() {
	if(fd) return 0;
	fd = fopen(sourcefile, "rb+");
	return !!fd;
}

int fileDescriptorFail() {
	return !fd && !openFileDescriptor();
}

int setSourcefile(char const *path) {
	if (access(path, F_OK | R_OK | W_OK) == -1) return -1;
	sourcefile = strdup(path);
	return openFileDescriptor() ? 0 : -1;
}

int readImage(int startPos, int endPos, uint8_t* buffer) {
	if(fileDescriptorFail()) return -1;
	fseek(fd, startPos, SEEK_SET);
	return fread(buffer, 1, endPos - startPos, fd);
}

int writeImage(int startPos, int endPos, uint8_t const * data) {
	if(fileDescriptorFail()) return -1;
	fseek(fd, startPos, SEEK_SET);
	return fwrite(data, 1, endPos - startPos, fd);
}
