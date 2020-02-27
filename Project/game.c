#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "declarations.h"  /* Declatations for these labs */
#include "objects.h"

void game(void)
{
   display_update();
   while(1)
   {
      setPixel(1, 2);
      setPixel(2, 3);
      setPixel(16, 64);
   }
}
