#include "file.h"	

// This fseek method has a file size limit of 4G. This shouldn't be an issue for what I'm doing with it, but it should be noted.
// REALLY REALLY wouldn't want a 4G pointer anyways.
char* read_file(char* fileName) {
	char *buffer = 0;
	long length;

	//TODO: Add Error checking
	FILE *f = fopen ("/home/arch/code/c/SNSyncUtil/SNSyncConfig.txt", "rb");
	if (f) {
		fseek (f, 0, SEEK_END);
		length = ftell (f);
		fseek (f, 0, SEEK_SET);
		buffer = malloc (length + 1);
		if (buffer) {
			fread (buffer, 1, length, f);
		}
		fclose (f);
		buffer[length] = '\0';
	}

	return buffer;
}
