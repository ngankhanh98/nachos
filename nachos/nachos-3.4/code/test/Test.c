#include<syscall.h>

int main()
{
	int ping, pong;
	PrintString("Test Do An 3 ping - pong.../n/n");
	ping = Exec("./test/ping");
	pong = Exec(".test/pong");
	Join(ping);
	Join(pong);
}
