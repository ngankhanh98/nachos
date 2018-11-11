#include "syscall.h"
#include "copyright.h"

#define MAX_LENGTH 255

#define STDIN 0
#define STDOUT 1

int main()
{
	char *a;
	Print("----------------------------------\0");
	Print("Enter a string: \0");
	Scan(a, MAX_LENGTH);
	Print(a);	
	return 0;
}
