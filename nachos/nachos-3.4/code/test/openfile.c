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
	char b[10];
	
	char *a = "anskg/smgfsdgr\0";
	Open("3.txt",0);	// index = 2 - WR
	Open("1.txt",1);	// index = 3 - RO
	Open("11.txt", 0); 	// index = 4 - WR


	Read(b,10,3);
	//Read(a,10,2);
	Write(b,10,4);
	//Write(a,10,STDOUT);
	//CloseFile(1);
	
	//Write(a,10,4);
	//Write(a,12,2);
	return 0;
}
