#include "syscall.h"
#include "copyright.h"

int main()
{
	//Open("stdin",1);	
	//Open("stdout",0);
	//Open("1.txt",1);
	
	//CloseFile(1);
	//CloseFile(3);

	char a[10];
	Open("3.txt",1);
	Open("1.txt",0);
	Read(a,125,3);
	
	//return 0;
}
