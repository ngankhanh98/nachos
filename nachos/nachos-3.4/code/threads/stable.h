#ifndef STABLE_H
#define STABLE_H
#define MAX_SEMAPHORE 10

#include "thread.h"
#include "synch.h"
#include "sem.h"
#include "bitmap.h"

class Stable
{
private:

	BitMap* bm;
	Sem* semTab[MAX_SEMAPHORE];

public:

	STable();
	~STable();
	int Create(char* name, int init);
	int Wait(char* name);
	int Signal(char* name);
	int FindFreeSlot(int id);

};

//*********************************************************************************************************************

#endif