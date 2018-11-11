#include "syscall.h"
#include "copyright.h"

#define MAX_LENGTH 255

#define STDIN 0
#define STDOUT 1

int main(int argc, char* argv[])
{
	OpenFileId fileId;
	int i = 0;
	char *c;
	int filesz;
	char name[MAX_LENGTH];
	char content[MAX_LENGTH];

	Print("Input file name:");
	Scan(name, MAX_LENGTH);
	
	fileId = Open(name, 0);
	Seek(0, name);
	
	Print("Input content: ");
	Scan(content, MAX_LENGTH);
	
	Write(content, MAX_LENGTH, fileId);
	CloseFile(name);
	
	CloseFile(fileId);
	return 0;
}
