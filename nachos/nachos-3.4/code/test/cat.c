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
	
	Print("Input file name:");
	Scan(name, MAX_LENGTH);
	if ((fileId = Open(name, 1)) == -1)
	{
		Print("Can not open file ");
		return 0;
	}
	filesz = Seek(-1, fileId);
	i = Seek(0, fileId);

	while(i<filesz)
	{	
		Read(c,1, 2);
		Print(c);
		i++;
	}
	
	CloseFile(fileId);
	return 0;
}
