#include "syscall.h"
#include "copyright.h"

#define MAX_LENGTH 255

int main(int argc, char* argv[])
{
	OpenFileId src_file, des_file;
	int i = 0;
	char *c;
	int filesz;
	char src[MAX_LENGTH], des[MAX_LENGTH];
	
	Print("Input source file name:");
	Scan(src, MAX_LENGTH);

	if ((src_file = Open(src, 1)) == -1)	// read-only
	{
		Print("Can not open source file\n");
		return 0;
	}

	Print("Input destinate file name:");
	Scan(des, MAX_LENGTH);

	if ((des_file = Open(des, 0)) == -1)	// readable & writeable
	{
		Print("Can not open destinate file\n");
		Print("Want to create new file? (Y/n)");
		Scan(c, MAX_LENGTH);

		if(c[0] == "n" || c[0] == "N")
			return 0;
		else
		{
			Print("Input new file name:");
			Scan(des, MAX_LENGTH);
			CreateFile(des);
			des_file = Open(des, 0);			
		}
	}

	filesz = Seek(-1, src_file);
	Seek(0, src_file);

	Seek(-1, des_file);
	while(i<filesz)
	{	
		Read(c,1, src_file);
		Write(c, 1, des_file);
		i++;
	}
	
	CloseFile(src_file);
	CloseFile(des_file);
	return 0;
}
