/* menu.c
   This file was written 2020 by Jack Webb and Amir Safizadeh,
   Last update 2020-02-27 */

#include <stdint.h>
#include <pic32mx.h>
#include "declarations.h"

char difficulty[] = "Easy";
char mode[] = "Singleplayer";
int timeoutcount = 0;
int modes = 0;
int winner;

void user_isr( void )
{
   if(IFS(0) & 0x100)
   {
      IFS(0) = 0;
      timeoutcount++;
   }
   if(timeoutcount == 5)
   {
      if(modes == 1)
      {
      display_string(2, difficulty);
      display_string(3, mode);
      display_update();
      display_image(96, icon);
      }
      timeoutcount = 0;
   }

   return;
}

void startscreen(void)
{
   clear_screen();
   display_string(2, "Switch=Difficuly");
   display_string(3, "Buttons=Start");
   display_update();
   while(1)
   {
      if(getbtns())
         break;
   }
}

void menu(void)
{
   int i;
   display_string(0, "PONG");
   display_string(1, "UNLIMITED");
   display_update();
   display_image(96, icon);
   modes = 1;
   while(getbtns()){} //To make sure it does not skip the menu
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
