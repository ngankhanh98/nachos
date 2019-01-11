#ifndef SEM_H
#define SEM_H

#include "thread.h"
#include "synch.h"

private:
	char name[50];
	Semaphore *sem; // Tạo Semaphore để quản lý
public:

	Sem(char* na, int i);
	~Sem();
	void wait();
	void signal();
	char* GetName();
} 
#endif