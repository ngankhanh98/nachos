#include "syscall.h"
#include "copyright.h"

int main()
{
	
	if(Open("text.txt", 1)!=-1)
		CreateFile("hcm.c");	// create

	Halt();
}
