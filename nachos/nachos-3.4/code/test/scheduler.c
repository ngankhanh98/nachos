#include "syscall.h"
#include "copyright.h"

void main(){
    int pingID, pongID;
    Print("Ping-pong test starting...\n\n");    

    pingID = Exec("./test/ping");
    pongID = Exec("./test/pong");
    //Join(0);
    //Join(1);
   while(1){};
}