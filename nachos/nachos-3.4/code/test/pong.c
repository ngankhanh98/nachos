#include "syscall.h"
#include "copyright.h"

// void PrintString(int i){
//     char *a;
//     int pos = 0;
//     int last;
//     char temp;
//     while(i)
//     {
//         a[pos] = (i%10) + '0';
//         i/=10;
//         pos++;
//     }
//     last = pos;
//     pos = 0;
//     while(pos<last)
//     {
//         temp = a[last];
//         a[last] = a[pos];
//         a[pos] = temp;
//         pos++;
//         last--;
//     }
//     //Print("\n");
//     Print(a);
//     Print("o\n");
// }

// int main(){
//     int i = 0;
//     while(i++<1000)
//     {
//         PrintString(i);
//     }
//     return 0;
// }

void main()
{
    int i=0;
    while(i++<1000)
    {
        PrintChar('B');
    }
}