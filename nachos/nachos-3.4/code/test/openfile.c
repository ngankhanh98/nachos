#include "syscall.h"
#include "copyright.h"

int main()
{
	OpenFileId open;
	open = Open("text.txt", 1);
	Halt();
	return 0;
}
