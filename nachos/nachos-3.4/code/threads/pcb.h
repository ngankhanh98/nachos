#ifndef PCB_H
#define PCB_H

#include "thread.h"
#include "synch.h"

class PCB
{
private:
	Semaphore	*joinsem;	//semaphore cho qua trinh join
	Semaphore	*exitsem;	//semaphore cho qua trinh exit
	Semaphore	*mutex;
	
	int		exitcode;	
	int		numwait;	//so tien trinh da join

	int pid;
	Thread *thread;
public:
	int 	parentID;	//ID cua tien trinh cha
	PCB(int id);
	~PCB();
	
	int Exec(char *filename, int pID); //nap chuong trinh co ten luu trong bien filename va processID se la pID
	int GetID();
	int GetNumWait();
	
	void JoinWait();
	void ExitWait();
	void JoinRelease();
	void ExitRelease();
	
	void IncNumWait();
	void DecNumWait();
	
	void SetExitCode(int ec);
	int GetExitCode();
	
	void SetFileName(char* fn);	// add
	char* GetFileName();
};

//*********************************************************************************************************************
void MyStartProcess(int);

#endif