
#include <file_access.h>

#include <string.h>
#include <errno.h>
#include <unistd.h>

char* sourcefile;

int setSourcefile(char const* path) {
	
	if( access(path, F_OK | R_OK | W_OK ) == -1 ) {
		errno = ENOENT;
		return -1;
	}
	
	char const* pathcpy = path;
	int pathlength = 1;
	while(*pathcpy++) pathlength++;
	char sourcefile[pathlength];
	strcpy(sourcefile, path);
	
	return 0;
}
