/* io.c
   This file was written 2020 by Jack Webb and Amir Safizadeh,
   Last update 2020-02-27 */



#include <stdint.h>
#include <pic32mx.h>
#include "declarations.h"


int getsw(void)
{
   int SW = (PORTD >> 8) & 0x000f;
   return SW;

}

int getbtns(void)
{
   int BTN = ((PORTD >> 4) & 0x000e) | ((PORTF >> 1) & 0x0001);
   return BTN;
}
