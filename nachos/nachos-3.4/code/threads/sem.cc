#include "sem.h"

Sem::Sem(char* na, int i) {
	strcpy(this->name, na);
	sem = new Semaphore(name, i);
}
Sem::~Sem() {
	delete sem;
}
void Sem::wait() {
	sem->P();
}
void Sem::signal() {
	sem->V();
}
char* Sem::GetName() {
	return name;
}