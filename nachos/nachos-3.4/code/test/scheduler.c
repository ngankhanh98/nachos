#include "syscall.h"
#include "copyright.h"

int main(){
    Exec("./test/ping");
    Exec("./test/pong");
    while(1){};
}