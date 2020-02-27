#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mips.h"  /* Declatations for these labs */
#define TMR2PERIOD ((80000000 / 256) / 10)

char difficulty[] = "Easy";
char mode[] = "Singleplayer";
int timeoutcount = 0;

void user_isr( void )
{
   if(IFS(0) & 0x100)
   {
      IFS(0) = 0;
      timeoutcount++;
   }
   if(timeoutcount == 10)
   {
      display_string(2, difficulty);
      display_string(3, mode);
      display_image(96, icon);
      display_update();
   }
   return;
}

void init( void )
{
   T2CON = 0x60;        //Set TCKPS to 110, thus prescale value to 64.
   TMR2 = 0x0;          //Initialize count to 0.
   PR2 = TMR2PERIOD;    //Set period between ticks to 10 ms.
   T2CONSET = 0x8000;   //Set bit 15 to 1, thus turn on timer.


   TRISESET = 0xff00;
   TRISDSET = 0x0fe0;
   PORTESET = 0;
   TRISFSET = 0x0002;

   IPC(2) |= 0x4;
   IEC(0) |= 0x100;
   enable_interrupt();
   return;
}

void menu(void)
{
   int sw = getsw();
   if(sw)
   {
      if(sw & 0x2)
         strcopy(difficulty, "Medium");

      else if(sw & 0x4)
         strcopy(difficulty, "Hard");
      else
         strcopy(difficulty, "Easy");

      if(sw & 0x8)
         strcopy(mode, "Multiplayer");
      else
         strcopy(mode, "Singleplayer");
   }
   // if(IFS(0) & 0x100)
   // {
   //    IFS(0) = 0;
   // //delay( 1000 );
   //    time2string( textstring, mytime );
   //    display_string( 3, textstring );
   //    display_update();
   //    tick( &mytime );
   //    display_image(96, icon);
   //    *portE = *portE + 1;
   // }

}
