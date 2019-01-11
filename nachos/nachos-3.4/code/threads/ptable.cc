#include "ptable.h"
#include "system.h"

PTable::PTable(int size)
{
	int i = 0;
	psize = MAX_PROCESS;
	bm = new BitMap(size);
	bmsem = new Semaphore("BMsem", 1);

	for (i = 0; i < MAX_PROCESS; i++)
		pcb[i] = NULL;
	bm->Mark(0);
}

// Bug-able, delete *bm??
PTable::~PTable()
{
	if (bm != NULL)
		delete bm;
	if (bmsem != NULL)
		delete bmsem;
	for (int i = 0; i < MAX_PROCESS; i++)
		if (pcb[i] != NULL)
			delete pcb[i];
}

//--------------------------------------------------------------------

int PTable::ExecUpdate(char *filename)
{
	bmsem->P(); //chi nap 1 tien trinh vao mot thoi diem

	//Kiem tra file co ton tai tren may khong
	OpenFile *execution = fileSystem->Open(filename);
	if (execution == NULL)
	{
		printf("\nUnable to open file %s\n", filename);
		bmsem->V();
		return -1;
	}
	delete execution; // close file
					  ////////////////////////////////////////////////////////////

	//Kiem tra chuong trinh duoc goi co la chinh no khong
	if (!strcmp(filename, currentThread->getName()))
	{
		printf("\nError: Process tries to execute itself\n");
		bmsem->V();
		return -1;
	}
	////////////////////////////////////////////////////////////

	//Kiem tra con slot trong khong
	int ID = GetFreeSlot();
	if (ID == -1)
	{
		printf("\nError: No more space for new process\n");
		bmsem->V();
		return -1;
	}
	////////////////////////////////////////////////////////////

	pcb[ID] = new PCB(ID);
	bm->Mark(ID);
	pcb[ID]->parentID = currentThread->ID;
	int pID = pcb[ID]->Exec(filename, ID);

	bmsem->V();
	return pID;
}

int PTable::ExitUpdate(int ec)
{
	//Kiem tra pID co ton tai khong
	int pID = currentThread->ID;
	if (!IsExist(pID))
	{
		printf("\nError: Unavailable process\n");
		return -1;
	}
	//////////////////////////////////////////////////////////////

	//Neu la main process thi Halt()
	if (pID == 0)
	{
		interrupt->Halt();
		return 0;
	}
	/////////////////////////////////////////////////////////////

	pcb[pID]->SetExitCode(ec);
	pcb[pcb[pID]->parentID]->DecNumWait();

	pcb[pID]->JoinRelease();
	pcb[pID]->ExitWait();
	Remove(pID);
	return ec;
}

int PTable::JoinUpdate(int pID)
{

	if (pID <= 0 || pID > 9)
	{
		printf("\nError: Unavailable process: id = %d\n", pID);
		return -1;
	}

	if (pcb[pID] == NULL)
	{
		printf("\nError: Unavailable process");
		return -1;
	}

	//kiem tra tien trinh dang chay co la cha cua tien trinh can join hay khong
	if (currentThread->ID != pcb[pID]->parentID)
	{
		printf("\nError: Process tries to join not parent process\n");
		return -1;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////

	pcb[pcb[pID]->parentID]->IncNumWait();
	pcb[pID]->JoinWait(); //doi den khi tien trinh con ket thuc

	int ec = pcb[pID]->GetExitCode();

	if (ec != 0)
	{
		printf("\nProcess exit with exitcode EC = %d ", ec);
		return -1;
	}

	pcb[pID]->ExitRelease(); //cho phep tien trinh con ket thuc
	return 0;
}

void PTable::Remove(int pID)
{
	if (pID < 0 || pID > 9)
		return;
	if (bm->Test(pID))
	{
		bm->Clear(pID);
		delete pcb[pID];
	}
}

//----------------------------------------------------------------------------------------------
int PTable::GetFreeSlot()
{
	return bm->Find();
}

bool PTable::IsExist(int pID)
{
	if (pID < 0 || pID > 9)
		return 0;
	return bm->Test(pID);
}

char *PTable::GetFileName(int pID)
{
	if (pID >= 0 && pID < 10 && bm->Test(pID))
		return pcb[pID]->GetFileName();
}
