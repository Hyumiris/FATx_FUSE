
#include <stdint.h>

extern char *sourcefile;

/*
	enables access to the image file
	returns 0, -1 on failure
*/
int setSourcefile(char const *path);

/*
	reads bytes from the image into the buffer [startPos, endPos)
	returns number of read bytes, -1 on failure
 */
int readImage(int startPos, int endPos, uint8_t* data);

/*
	writes bytes from the buffer into the image [startPos, endPos)
	returns number of written bytes, -1 on failure
 */
int writeImage(int startPos, int endPos, uint8_t const * data);

