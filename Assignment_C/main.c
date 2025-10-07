#include"add.h"//included the function prototypes
#define red 01
#define blue 02
#define green 03
#define PI 3.14159
__attribute__((section(".krishnaveni")))

int gvar1;
int gavr3 = green;
const int gvar5 = 20;
void main()
{
#ifdef red
    gvar1 = add_two(5 , red);//calling function
    gvar1 += red + blue + PI;
#endif
    while(1);
}