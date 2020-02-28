#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "declarations.h"  /* Declatations for these labs */
#include "objects.h"

Ball ball;
Paddle paddle1;
Paddle paddle2;
// 1 = game ongoing. 2 = score. 0 = game over.
int gamestate = 1;
int directionRight   = 1;
int directionUp      = 1;
int btns;

void move_paddle(int btns)
{
   if((paddle2.y != 30) && (btns & 0x1))
      paddle2.y = paddle2.y + 1;
   if((paddle2.y != 1) && (btns & 0x2))
      paddle2.y = paddle2.y - 1;

   if((paddle1.y != 30) && (btns & 0x4))
      paddle1.y = paddle1.y + 1;
   if((paddle1.y != 1) && (btns & 0x8))
      paddle1.y = paddle1.y - 1;
}

void move_ball(void)
{
   if((ball.y == 0) || (ball.y == 31))
      directionUp = !directionUp;
   if((ball.x == 0) || (ball.x == 127))
      directionRight = !directionRight;
   if((ball.x == paddle1.x) && (ball.y == paddle1.y))
      directionRight = !directionRight;

   if(directionRight)
      ball.x = ball.x + 1;
   else if(!directionRight)
      ball.x = ball.x - 1;
   if(directionUp)
      ball.y = ball.y - 1;
   else if(!directionUp)
      ball.y = ball.y + 1;
}

void game(void)
{
   //Initialize ball
   ball.x = 64;
   ball.y = 16;
   ball.speedX = 1;
   ball.speedY = 1;
   //Initialize player 1 paddle
   paddle1.x = 3;
   paddle1.y = 13;
   paddle1.speed = 10;
   paddle1.score = 0;
   //Initialize player 2 paddle
   paddle2.x = 124;
   paddle2.y = 13;
   paddle2.speed = 10;
   paddle2.score = 0;

   set_pixel(ball.x, ball.y);
   set_pixel(paddle1.x, paddle1.y);
   set_pixel(paddle2.x, paddle2.y);
   update_screen();

   while(1)
   {
      int i;
      clear_screen();
      move_ball();
      btns = getbtns();
      if(btns)
         move_paddle(btns);
      set_pixel(ball.x, ball.y);
      set_pixel(paddle1.x, paddle1.y);
      set_pixel(paddle2.x, paddle2.y);
      for(i = 0; i < 0xFFFF; i++);
      update_screen();
   }
}
