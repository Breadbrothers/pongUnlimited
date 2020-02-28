/**   Contents of this file is based on the file "mipslabwork.c"
*     2015 by F Lundevall
*/

#include <stdint.h>
#include <pic32mx.h>
#include "declarations.h"
#include "objects.h"

//Declare some helper function for this file (funcs.c)
static void num32asc(char* s, int );

#define DISPLAY_CMD_MODE   (PORTFCLR = 0x10)
#define DISPLAY_DATA_MODE  (PORTFSET = 0X10)

#define DISPLAY_ACTIVATE_RESET   (PORTGCLR = 0x200)
#define DISPLAY_DO_NO_RESET      (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD  (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_VDD_OFF    (PORTFSET = 0x40)
#define DISPLAY_VBAT_OFF   (PORTFSET = 0X20)


void quicksleep(int cyc)
{
   int i;
   for(i = cyc; i > 0; i--);
}

void display_debug(volatile int* const addr)
{
   display_string(1, "Addr");
   display_string(2, "Data");
   num32asc(&textbuffer[1][6], (int) addr );
   num32asc(&textbuffer [2][6], *addr);
   display_update();
}

//SPI2 helper fucntion to determine if interface ready
uint8_t spi_send_recv(uint8_t data)
{
   while(!(SPI2STAT & 0x08));
   SPI2BUF = data;
   while(!(SPI2STAT & 1));
   return SPI2BUF;
}

//OLED Screen initialization
void display_init(void)
{
   DISPLAY_CMD_MODE;
   quicksleep(10);
   DISPLAY_ACTIVATE_VDD;
   quicksleep(1000000);

   spi_send_recv(0xAE);
   DISPLAY_ACTIVATE_RESET;
   quicksleep(10);
   DISPLAY_DO_NO_RESET;
   quicksleep(10);

   spi_send_recv(0x8D);
   spi_send_recv(0x14);
   spi_send_recv(0xD9);
   spi_send_recv(0xF1);

   DISPLAY_ACTIVATE_VBAT;
   quicksleep(10000000);

   spi_send_recv(0xA1);
   spi_send_recv(0xC8);
   spi_send_recv(0xDA);
   spi_send_recv(0x20);
   spi_send_recv(0xAF);
}

//Function to display a string on screen
void display_string(int line, char* s)
{
   int i;
   if(line < 0 || line >= 4)
      return;
   if(!s)
      return;

   for(i = 0; i < 16; i++)
      if(*s)
      {
         textbuffer[line][i] = *s;
         s++;
      }
      else
         textbuffer[line][i] = ' ';
}

void clear_text()
{
   int row, j;
   for(row = 0; row < 4; row++)
      for(j = 0; j < 16; j++)
         textbuffer[row][j] = ' ';
}
//Displays a 32x32 image
void display_image(const int x, const uint8_t *data)
{
   int row, col;
   //4 rows across the display
   //each row is 32 cols wide each col is 8 bits high.
   for(row = 0; row < 4; row++)
   {
      DISPLAY_CMD_MODE;

      spi_send_recv(0x22); //Cmd to set the row
      spi_send_recv(row); //Set current row

      spi_send_recv(x & 0xF);
      spi_send_recv(0x10 | ((x >> 4) & 0xF));

      DISPLAY_DATA_MODE;

      //col is x axis of current row
      for(col = 0; col < 32; col++)
         spi_send_recv(~data[row*32 + col]);
   }
}

void display_update(void)
{
   int row, col, bit;
   int c;
   //Textbuffer has 4 rows and 16 cols
   for(row = 0; row < 4; row++)
   {
      DISPLAY_CMD_MODE;
      spi_send_recv(0x22);
      spi_send_recv(row);
      spi_send_recv(0x0);
      spi_send_recv(0x10);

      DISPLAY_DATA_MODE;

      for(col = 0; col < 16; col++)
      {
         c = textbuffer[row][col];
         if(c & 0x80)
            continue;
         for(bit = 0; bit < 8; bit++)
            spi_send_recv(font[c*8 + bit]);
      }
   }
}

//Converts a number to hexadecimal ASCII digits.
static void num32asc(char* s, int n)
{
   int i;
   for(i = 28; i >= 0; i -= 4)
      *s++ = "0123456789ABCDEF"[(n >> i) & 15];
}

char *strcopy(char* destination, char* source)
{
   char* start = destination;

   while(*source != '\0')
   {
      *destination = *source;
      destination++;
      source++;
   }
   *destination = '\0';
   return start;
}

void update_screen(const uint8_t *data)
{
   int row, col, bit;
   int c;
   for(row = 0; row < 4; row++)
   {
      DISPLAY_CMD_MODE;
      spi_send_recv(0x22);
      spi_send_recv(row);
      spi_send_recv(0x0);
      spi_send_recv(0x10);
      DISPLAY_DATA_MODE;
      for(col = 0; col < 128; col++)
      {
         spi_send_recv(screen[row * 128 + col]);
      }
   }
}

void clear_screen(void)
{
   int i;
   for(i = 0; i < 512; i++)
      screen[i] = 0;
}

void set_pixel(int x, int y)
{
   short offset = 0;
   if(y > 0)
      offset = y / 8;
   screen[offset * 128 + x] |= 1 << (y - offset * 8);
}
