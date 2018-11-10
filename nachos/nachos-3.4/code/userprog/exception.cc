// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"

#define MaxFileLength 32

//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	are in machine.h.
//----------------------------------------------------------------------

// Input: - User space address (int)
// - Limit of buffer (int)
// Output:- Buffer (char*)
// Purpose: Copy buffer from User memory space to System memory space
char* User2System(int virtAddr, int limit)
{
	int i; //chi so index
	int oneChar;
	char* kernelBuf = NULL;
	kernelBuf = new char[limit + 1]; //can cho chuoi terminal
	if (kernelBuf == NULL)
		return kernelBuf;
		
	memset(kernelBuf, 0, limit + 1);
	
	for (i = 0; i < limit; i++)
	{
		machine->ReadMem(virtAddr + i, 1, &oneChar);
		kernelBuf[i] = (char)oneChar;
		if (oneChar == 0)
			break;
	}
	return kernelBuf;
}

// Input: - User space address (int)
// - Limit of buffer (int)
// - Buffer (char[])
// Output:- Number of bytes copied (int)
// Purpose: Copy buffer from System memory space to User memory space
int System2User(int virtAddr, int len, char* buffer)
{
	if (len < 0) return -1;
	if (len == 0)return len;
	int i = 0;
	int oneChar = 0;
	do{
		oneChar = (int)buffer[i];
		machine->WriteMem(virtAddr + i, 1, oneChar);
		i++;
	} while (i < len && oneChar != 0);
	return i;
}

// Inscrease program counter
// Pre-PC register assigned by PC register
// PC register assigned by Next-PC register
// Next-PC resgister assigned by 4-byte ahead register
void InscreasePC()
{
	machine->registers[PrevPCReg] = machine->registers[PCReg];
	machine->registers[PCReg] = machine->registers[NextPCReg];
	machine->registers[NextPCReg] += 4;	
	//int counter = machine->ReadRegister(PCReg);
   	//machine->WriteRegister(PrevPCReg, counter);
    	//counter = machine->ReadRegister(NextPCReg);
    	//machine->WriteRegister(PCReg, counter);
   	//machine->WriteRegister(NextPCReg, counter + 4);
}

// Ham xu ly ngoai le runtime Exception va system call
void ExceptionHandler(ExceptionType which)
{
    int type = machine->ReadRegister(2);

	// Bien toan cuc cho lop SynchConsole
	
	
	//Bat dau
	switch (which) {
	case NoException:
		return;

	case PageFaultException:
		DEBUG('a', "\nNo valid translation found");
		printf("\nNo valid translation found");
		interrupt->Halt();
		break;

	case ReadOnlyException:
		DEBUG('a', "\nWrite attempted to page marked \"read-only\"");
		printf("\nWrite attempted to page marked \"read-only\"");
		interrupt->Halt();
		break;

	case BusErrorException:
		DEBUG('a', "\nTranslation resulted in an invalid physical address");
		printf("\nTranslation resulted in an invalid physical address");
		interrupt->Halt();
		break;

	case AddressErrorException:
		DEBUG('a', "\nUnaligned reference or one that was beyond the end of the address space");
		printf("\nUnaligned reference or one that was beyond the end of the address space");
		interrupt->Halt();
		break;

	case OverflowException:
		DEBUG('a', "\nInteger overflow in add or sub.");
		printf("\nInteger overflow in add or sub.");
		interrupt->Halt();
		break;

	case IllegalInstrException:
		DEBUG('a', "\nUnimplemented or reserved instr.");
		printf("\nUnimplemented or reserved instr.");
		interrupt->Halt();
		break;

	case NumExceptionTypes:
		DEBUG('a', "\nNumExceptionTypes");
		printf("\nNumExceptionTypes");
		interrupt->Halt();
		break;

	case SyscallException:
		switch (type){

		case SC_Halt:
			// Input: Khong co
			// Output: Thong bao tat may
			// Chuc nang: Tat HDH
			DEBUG('a', "\nShutdown, initiated by user program. ");
			printf("\nShutdown, initiated by user program. ");
			interrupt->Halt();
			break;
		case SC_CreateFile:
		{
			// Input: Dia chi tu vung nho user cua ten file
			// Output: -1 = Loi, 0 = Thanh cong
			// Chuc nang: Tao ra file voi tham so la ten file
			int virtAddr;
			char* filename;
			DEBUG('a', "\n SC_CreateFile call ...");
			DEBUG('a', "\n Reading virtual address of filename");

			virtAddr = machine->ReadRegister(4); //Doc dia chi cua file tu thanh ghi R4
			DEBUG('a', "\n Reading filename.");
			
			//Sao chep khong gian bo nho User sang System, voi do dang toi da la (32 + 1) bytes
			filename = User2System(virtAddr, MaxFileLength + 1);
			if (strlen(filename) == 0)
			{
				printf("\n File name is not valid");
				DEBUG('a', "\n File name is not valid");
				machine->WriteRegister(2, -1); //Return -1 vao thanh ghi R2
				//IncreasePC();
				//return;
				break;
			}
			
			if (filename == NULL)  //Neu khong doc duoc
			{
				printf("\n Not enough memory in system");
				DEBUG('a', "\n Not enough memory in system");
				machine->WriteRegister(2, -1); //Return -1 vao thanh ghi R2
				delete filename;
				//IncreasePC();
				//return;
				break;
			}
			DEBUG('a', "\n Finish reading filename.");
			
			if (!fileSystem->Create(filename, 0)) //Tao file bang ham Create cua fileSystem, tra ve ket qua
			{
				//Tao file that bai
				printf("\n Error create file '%s'", filename);
				machine->WriteRegister(2, -1);
				delete filename;
				//IncreasePC();
				//return;
				break;
			}
			
			//Tao file thanh cong
			machine->WriteRegister(2, 0);
			printf("\nCreate file success");
			delete filename;
			//IncreasePC(); //Day thanh ghi lui ve sau de tiep tuc ghi
			//return;
			break;
		}
		case SC_Open:
		{
			int bufAddr = machine->ReadRegister(4); // read string pointer from user
			int type = machine->ReadRegister(5);
			char *buf;


					if (fileSystem->index > 10)
					{
						machine->WriteRegister(2, -1);
						break;
					}
					buf = User2System(bufAddr, MaxFileLength + 1);
					if (strcmp(buf,"stdin") == 0)
					{
						printf("Stdin mode\n");	
						//fileSystem->index++;
						machine->WriteRegister(2, 0);
						break;
					}
					if (strcmp(buf,"stdout") == 0)
					{
						printf("Stdout mode\n");
						//fileSystem->index++;
						machine->WriteRegister(2, 1);
						break;
					}
					
					if ((fileSystem->Open(buf,type)) != NULL)
					{
						
						printf("Open file success '%s'\n", buf);
						machine->WriteRegister(2, fileSystem->index-1);
					} else 
					{
						printf("Can not open file '%s'",buf);
						machine->WriteRegister(2, -1);
					};
			delete[] buf;
			break;
					
		}	
		case SC_Close:
		{
			int no = machine->ReadRegister(4);
			int i = fileSystem->index;	

			if(i < no) 
			{
				printf("Close file failed \n");
				machine->WriteRegister(2, -1);
				break;
			}
			
			fileSystem->openfile[no] == NULL;
			//delete fileSystem->openfile[no];		
			machine->WriteRegister(2, 0);
			printf("Close file success \n");
			break;
		}
	
		}
	}
	if(which!=SC_Halt)
	InscreasePC();
}
