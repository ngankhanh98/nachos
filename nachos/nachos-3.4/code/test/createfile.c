#include "syscall.h"
#include "copyright.h"

#define MAX_LENGTH 255
#define STDIN 0
#define STDOUT 1

int main(int argc, char* argv[])
{
	char *a;
	char *filename;	
	
	Print("----------------------------------\n\0");
	Print("Enter filename: \0");
	Scan(filename, MAX_LENGTH);
	
	CreateFile(filename);
	
	return 0;
}
