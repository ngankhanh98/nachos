#include "syscall.h"
#include "copyright.h"


#define STDIN 0
#define STDOUT 1
int main()
{
	//Open("stdin",1);	
	//Open("stdout",0);
	//Open("1.txt",1);
	
	//CloseFile(1);
	//CloseFile(3);
	
	char *a  = "kwfs,zdfnsddfa\0";
	Open("3.txt",0);	// index = 2 - WR
	Open("1.txt",1);	// index = 3 - RO
	//Read(a,10,3);
	//Write(a,10,STDOUT);
	Write(a,12,2);
	//Write(a,12,2);
	return 0;
}
