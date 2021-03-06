#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "declarations.h"  /* Declatations for these labs */
#define TMR2PERIOD ((80000000 / 256) / 10)

void init( void )
{
   TRISESET = 0xff00;
   TRISDSET = 0x0fe0;
   PORTESET = 0;
   TRISFSET = 0x0002;

   T2CON = 0x70;
   PR2   = TMR2PERIOD;
   TMR2  = 0;
   T2CONSET = 0x8000;
   IPC(2)  |= 0x4;
   IEC(0)  |= 0x100;
   enable_interrupt();
   return;
}
