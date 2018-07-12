#define FUSE_USE_VERSION 26

#include <fuse.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#include <image_access.h>
#include <read_bootsec.h>
#include <file_allocation_table.h>

static const char *filepath = "/file";
static const char *filename = "file";
static const char *filecontent = "I'm the content of the only file available there\n";

static char* imagefile = NULL;

static int getattr_callback(const char *path, struct stat *stbuf)
{
	memset(stbuf, 0, sizeof(struct stat));

	if (strcmp(path, "/") == 0)
	{
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 2;
		return 0;
	}

	if (strcmp(path, filepath) == 0)
	{
		stbuf->st_mode = S_IFREG | 0777;
		stbuf->st_nlink = 1;
		stbuf->st_size = strlen(filecontent);
		return 0;
	}

	return -ENOENT;
}

static int readdir_callback(const char *path, void *buf, fuse_fill_dir_t filler,
							off_t offset, struct fuse_file_info *fi)
{
	(void)offset;
	(void)fi;

	filler(buf, ".", NULL, 0);
	filler(buf, "..", NULL, 0);

	filler(buf, filename, NULL, 0);

	return 0;
}

static int open_callback(const char *path, struct fuse_file_info *fi)
{
	return 0;
}

static int read_callback(const char *path, char *buf, size_t size, off_t offset,
						 struct fuse_file_info *fi)
{

	if (strcmp(path, filepath) == 0)
	{
		size_t len = strlen(filecontent);
		if (offset >= len)
		{
			return 0;
		}

		if (offset + size > len)
		{
			memcpy(buf, filecontent + offset, len - offset);
			return len - offset;
		}

		memcpy(buf, filecontent + offset, size);
		return size;
	}

	return -ENOENT;
}

static struct fuse_operations fuse_example_operations = {
	.getattr = getattr_callback,
	.open = open_callback,
	.read = read_callback,
	.readdir = readdir_callback,
};

int main(int argc, char *argv[])
{
	if(argc < 2) 		
		return -1;
	
	if(setSourcefile(argv[1])) {
		perror("no valid image file");
		return 1;
	}
	
	if (readBootsector(sourcefile))	{
		perror("reading bootsector failed");
		return 2;
	}

	char* normalArgs[argc - 1];
	normalArgs[0] = argv[0];
	for(int i = 2; i < argc; ++i)
		normalArgs[i - 1] = argv[i];

	
	printf("numberBytesPerBlock: %i \n", numberBytesPerBlock);
	printf("numberBlocksPerCluster: %i \n", numberBlocksPerCluster);
	printf("numberReservedSectors: %i \n", numberReservedSectors);
	printf("numberFATs: %i \n", numberFATs);
	printf("numberRootDirectories: %i \n", numberRootDirectories);
	printf("totalNumberBlocks: %i \n", totalNumberBlocks);
	printf("numberBlocksPerFAT: %i \n", numberBlocksPerFAT);
	printf("fat_x: %i \n", fat_x);

	printf("first entry: %lli \n", getFATEntry(0));
	printf("second entry: %lli \n", getFATEntry(1));


	return fuse_main(argc - 1, normalArgs, &fuse_example_operations, NULL);
}
