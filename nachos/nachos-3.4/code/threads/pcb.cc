#include "pcb.h"
#include "utility.h"
#include "system.h"
#include "thread.h"
#include "addrspace.h"

PCB::PCB(int id)
{
	joinsem = new Semaphore("JoinSem",0);
	exitsem = new Semaphore("ExitSem",0);
	mutex = new Semaphore("Mutex",1);
	
	exitcode = 0;
	numwait = 0;
	pid = id;
	if(id)
		parentID = currentThread->ID;
	else
		parentID = 0;
	thread = NULL;
}

PCB::~PCB()
{
	if(joinsem != NULL)
		delete joinsem;
	if(exitsem != NULL)
		delete exitsem;
	if(mutex != NULL)
		delete mutex;
}

//------------------------------------------------------------------
int PCB::GetID()
{
	return thread->ID;
}

int PCB::GetNumWait()
{
	return numwait;
}

int PCB::GetExitCode()
{
	return exitcode;	
}

void PCB::SetExitCode(int ec)
{
	exitcode = ec;
}

void PCB::IncNumWait()
{
	numwait++;
}

void PCB::DecNumWait()
{
	if(numwait)
		numwait--;
}

char* PCB::GetFileName()
{
	return thread->getName();
}

//-------------------------------------------------------------------
void PCB::JoinWait()
{
	IncNumWait();
	joinsem->P();
}

void PCB::JoinRelease()
{
	DecNumWait();
	joinsem->V();
}

void PCB::ExitWait()
{
	exitsem->P();
}

void PCB::ExitRelease()
{
	exitsem->V();
}

//------------------------------------------------------------------
int PCB::Exec(char *filename, int pID)
{
	mutex->P();
	thread = new Thread(filename);
	if(thread == NULL)
	{
		printf("\nLoi: Khong tao duoc tien trinh moi !!!\n");
		mutex->V();
		return -1;
	}
	thread->ID = pID;
	pid = pID;
	OpenFile *execution = fileSystem->Open(filename);
	AddrSpace *space = new AddrSpace(execution);
	if(space == NULL)
	{
		printf("\nLoi: Not enough space...\n");
		return; 
	}
	currentThread->space = space;

	thread->Fork(MyStartProcess,pID);
	mutex->V();
	return pID;
}


//*************************************************************************************
void MyStartProcess(int)
{
	

	currentThread->space->InitRegisters();		// set the initial register values
	currentThread->space->RestoreState();		// load page table register

	machine->Run();			// jump to the user progam
	ASSERT(FALSE);			// machine->Run never returns;
						// the address space exits
						// by doing the syscall "exit"
}