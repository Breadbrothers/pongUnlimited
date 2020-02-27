#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "declarations.h"  /* Declatations for these labs */

char difficulty[] = "Easy";
char mode[] = "Singleplayer";
int timeoutcount = 0;
int modes = 1;

void user_isr( void )
{
   if(modes){
   if(IFS(0) & 0x100)
   {
      IFS(0) = 0;
      timeoutcount++;
   }
   if(timeoutcount == 5)
   {
      display_string(2, difficulty);
      display_string(3, mode);
      display_update();
      display_image(96, icon);
      timeoutcount = 0;
   }
   }
   return;
}

void menu(void)
{
   display_string(0, "PONG");
   display_string(1, "UNLIMITED");
   display_update();
   display_image(96, icon);
   while(1)
   {
      int sw = getsw();
      if(sw)
      {
         if(sw & 0x2)
         strcopy(difficulty, "Medium"); //Switch 2
         else if(sw & 0x4)
         strcopy(difficulty, "Hard"); //Switch 3
         else
         strcopy(difficulty, "Easy");
         if(sw & 0x8)
         strcopy(mode, "Multiplayer"); //Switch 4
         else
         strcopy(mode, "Singleplayer");
      }
      else
      {
         strcopy(difficulty, "Easy");
         strcopy(mode, "Singleplayer");
      }
      if(getbtns())
      {
         modes = 0;
         break;
      }
   }
}
