#include"stable.h"

Stable::STable()
{
	bm = new BitMap(size);

	for (int i = 0; i < 10; i++) {
		semTab[i] = NULL;
	}
	bm->Mark(0);
}
Stable::~STable()
{
	if (bm != NULL)
		delete bm;
	for (int i = 0; i < MAX_SEMAPHORE; i++)
		if (semTab[i] != NULL)
			delete semTab[i];
}

// Kiem tra Semaphore "name"chua ton tai thi tao Semaphore moi
int Stable::Create(char* name, int init)
{
	int IsExist = 0;
	for (int i = 0; i < MAX_SEMAPHORE; i++) {
		if (name == semTab[i].name) IsExist = 1;
	}
	int position = FindFreeSlot(0);
	if (IsExist == 0) semTab[position] = new Sem(name, init);
	else return -1;
}
int Stable::Wait(char* name)
{
	int IsExist = 0;
	for (int i = 0; i < MAX_SEMAPHORE; i++) {
		if (name == semTab[i].name) IsExist = 1;
	}
	if (IsExist == 1) this->P();
	else return -1;
}
int Stable::Signal(char* name)
{
	int IsExist = 0;
	for (int i = 0; i < MAX_SEMAPHORE; i++) {
		if (name == semTab[i].name) IsExist = 1;
	}
	if (IsExist == 1) this->V();
	else return -1;
}
int Stable::FindFreeSlot(int id)
{
	for (int i = 0; i < MAX_SEMAPHORE; i++) {
		if (semTab[i].name == NULL) return i;
	}
}