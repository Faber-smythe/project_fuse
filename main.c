/*
	Not being a part of an ongoing project, this file has not been commented.
	It follows quite directly the basics of libfuse usage, which you can find there :
	https://github.com/libfuse/libfuse

	You will find some explanation about this specific file in the exercise's ReadMe :
	https://github.com/Faber-smythe/project_fuse/blob/master/README.md 

	Compile with :
  	gcc -Wall main.c `pkg-config fuse --cflags --libs` -o main
*/

#define FUSE_USE_VERSION 26

#include <stdlib.h>
#include <unistd.h>
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>


static const char *hello_str = "Hello World!\n";
static const char *hello_path = "/hello";

static const char *output_str = "Write something here and it should output in the console log !\n";
static const char *output_path = "/output";

static const char *shutdown_str = "Write something here and your machine should shut down !\n";
static const char *shutdown_path = "/shutdown";

static int custom_getattr(const char *path, struct stat *stbuf)
{
	int res = 0;

	memset(stbuf, 0, sizeof(struct stat));
	if (strcmp(path, "/") == 0) {
		stbuf->st_mode = S_IFDIR | 0444;
		stbuf->st_nlink = 2;
	} else if (strcmp(path, hello_path) == 0) {
		stbuf->st_mode = S_IFREG | 0444;
		stbuf->st_nlink = 1;
		stbuf->st_size = strlen(hello_str);
	} else if (strcmp(path, output_path) == 0) {
		stbuf->st_mode = S_IFREG | 0444;
		stbuf->st_nlink = 1;
		stbuf->st_size = strlen(output_str);
	} else if (strcmp(path, shutdown_path) == 0) {
		stbuf->st_mode = S_IFREG | 0444;
		stbuf->st_nlink = 1;
		stbuf->st_size = strlen(shutdown_str);
	} else
		res = -ENOENT;

	return res;
}

static int custom_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
			 off_t offset, struct fuse_file_info *fi)
{
	(void) offset;
	(void) fi;


	filler(buf, ".", NULL, 0);
	filler(buf, "..", NULL, 0);
	if (strcmp(path, "/") == 0){
		filler(buf, hello_path + 1, NULL, 0);
		filler(buf, output_path + 1, NULL, 0);
		filler(buf, shutdown_path + 1, NULL, 0);
	}else{
		return -ENOENT;
	}
	return 0;
}

static int custom_open(const char *path, struct fuse_file_info *fi)
{
	return 0;
}

static int custom_read(const char *path, char *buf, size_t size, off_t offset,
		      struct fuse_file_info *fi)
{
	size_t len;
	(void) fi;
	if(strcmp(path, hello_path) == 0){

		len = strlen(hello_str);
		if (offset < len) {
			if (offset + size > len)
				size = len - offset;
			memcpy(buf, hello_str + offset, size);
		} else
			size = 0;

		return size;
	}
	else if(strcmp(path, output_path) == 0){

		len = strlen(output_str);
		if (offset < len) {
			if (offset + size > len)
				size = len - offset;
			memcpy(buf, output_str + offset, size);
		} else
			size = 0;
			
		return size;
	}
	else if(strcmp(path, shutdown_path) == 0){

		len = strlen(shutdown_str);
		if (offset < len) {
			if (offset + size > len)
				size = len - offset;
			memcpy(buf, shutdown_str + offset, size);
		} else
			size = 0;
			
		return size;
	}
	else{

		return -ENOENT;
	}
}

static int custom_write(const char *path, const char *buf, size_t size,
		     off_t offset, struct fuse_file_info *fi)
{

	if(strcmp(path, output_path) == 0)
		printf("This just got written onto the %s file :\n%s\n", path, buf);
	
	if(strcmp(path, shutdown_path) == 0){
		printf("Shutting down now. Bye !\n");
		system("shutdown -P now");
	}
	
	return 0;
}

// listing implemented function
static struct fuse_operations hello_oper = {
	.getattr	= custom_getattr,
	.readdir	= custom_readdir,
	.open		= custom_open,
	.read		= custom_read,
	.write		= custom_write,
};

// entry point
int main(int argc, char *argv[])
{
	return fuse_main(argc, argv, &hello_oper, NULL);
}