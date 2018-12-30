#ifndef PTABLE_H
#define PTABLE_H

#include "bitmap.h"
#include "pcb.h"
#include "synch.h"

#define MAX_PROCESS 10

class PTable
{
  private:
	BitMap *bm;
	PCB *pcb[MAX_PROCESS];
	int psize;
	Semaphore *bmsem; //Dung de ngan chan truong hop nap 2 tien trinh cung luc

  public:
	PTable(int size);				//Khoi tao size doi tuong pcb de luu size process. Gan gia tri ban dau la null. Nho khoi tao *bm va *bmsem de su dung
	~PTable();						//Huy doi tuong da tao
	int ExecUpdate(char *filename); //return PID
	int ExitUpdate(int ec);
	int JoinUpdate(int id);
	int GetFreeSlot();		   //Tim slot trong de luu thong tin cho tien trinh moi
	bool IsExist(int pid);	 //Kiem tra co ton tai process ID nay khong
	void Remove(int pid);	  //Xoa mot processID ra khoi mang quan ly no, khi ma tien trinh nay da ket thuc
	char *GetFileName(int id); //Lay ten cua tien trinh co processID la pID
};
#endif