#include <stdint.h>
#include <pic32mx.h>
#include "declarations.h"
#include "objects.h"
//Object initialization
Ball ball;
Paddle paddle1;
Paddle paddle2;
Obstacle obstacle;

//Other variable initializations
int directionRight   = 1;
int directionUp      = 1;
int btns;
int scoreP1;
int scoreP2;
int def = 0xffff * 2;

// the paddles movment
void move_paddle(int btns)
{
   if((paddle2.y != 24) && (btns & 0x1))
      paddle2.y = paddle2.y + 1;
   if((paddle2.y != 0) && (btns & 0x2))
      paddle2.y = paddle2.y - 1;

   if((paddle1.y != 24) && (btns & 0x4))
      paddle1.y = paddle1.y + 1;
   if((paddle1.y != 0) && (btns & 0x8))
      paddle1.y = paddle1.y - 1;
}
// the paddles size
void set_paddle(Paddle p)
{
   set_pixel(p.x, p.y);
   set_pixel(p.x, p.y + 1);
   set_pixel(p.x, p.y + 2);
   set_pixel(p.x, p.y + 3);
   set_pixel(p.x, p.y + 4);
   set_pixel(p.x, p.y + 5);
   set_pixel(p.x, p.y + 6);
}
//the ball size
void set_ball(Ball b)
{
   set_pixel(b.x, b.y);
   set_pixel(b.x + 1, b.y);
   set_pixel(b.x, b.y + 1);
   set_pixel(b.x + 1, b.y + 1);
}
//ball movment
void move_ball(void)
{
   if((ball.y == 1) || (ball.y == 31))
      directionUp = !directionUp;
   if(ball.x == 0)
   {
      directionRight = !directionRight;
      scoreP2++;
      if(scoreP2 == 1)
         PORTESET = 1;
      if(scoreP2 == 2)
         PORTESET = 2;
      if(scoreP2 == 3)
         PORTESET = 4;
   }

   if(ball.x == 126)
   {
      directionRight = !directionRight;
      scoreP1++;
      if(scoreP1 == 1)
         PORTESET = 128;
      if(scoreP1 == 2)
         PORTESET = 64;
      if(scoreP1 == 3)
         PORTESET = 32;
   }

   if((ball.x == paddle1.x) && (ball.y == paddle1.y) ||
      (ball.x == paddle1.x) && (ball.y == paddle1.y + 1) ||
      (ball.x == paddle1.x) && (ball.y == paddle1.y + 2) ||
      (ball.x == paddle1.x) && (ball.y == paddle1.y + 3) ||
      (ball.x == paddle1.x) && (ball.y == paddle1.y + 4) ||
      (ball.x == paddle1.x) && (ball.y == paddle1.y + 5) ||
      (ball.x == paddle1.x) && (ball.y == paddle1.y + 6) ||

      (ball.x + 1 == paddle2.x) && (ball.y == paddle2.y) ||
      (ball.x + 1 == paddle2.x) && (ball.y == paddle2.y + 1) ||
      (ball.x + 1 == paddle2.x) && (ball.y == paddle2.y + 2) ||
      (ball.x + 1 == paddle2.x) && (ball.y == paddle2.y + 3) ||
      (ball.x + 1 == paddle2.x) && (ball.y == paddle2.y + 4) ||
      (ball.x + 1 == paddle2.x) && (ball.y == paddle2.y + 5) ||
      (ball.x + 1 == paddle2.x) && (ball.y == paddle2.y + 6))
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

void gameover(int winner)
{
   clear_screen();
   update_screen();
   while(1)
   {
      if(winner == 1)
      {
         display_string(0, "CONGRATULATIONS");
         display_string(1, "PLAYER 1 WON! :)");
         display_string(2, "TOO BAD PLAYER 2");
         display_string(3, "GET BETTER SOON!");
         display_update();
      }

      if(winner == 2)
      {
         display_string(0, "CONGRATULATIONS");
         display_string(1, "PLAYER 2 WON");
         display_string(2, "TOO BAD PLAYER 1");
         display_string(3, "Better luck next time");
         display_update();
      }
   }
}


void single_palyer( int btns){
  if(ball.y < 24)
paddle2.y = ball.y;

if((paddle1.y != 24) && (btns & 0x4))
   paddle1.y = paddle1.y + 1;
if((paddle1.y != 0) && (btns & 0x8))
   paddle1.y = paddle1.y - 1;
}

void set_obstacle(){
  int i,j;
  for(j = 61 ; j <= 62; j++){
   for(i = 6; i < 14; i++){
     set_pixel(obstacle.x = j, obstacle.y = i);
     set_pixel(obstacle.x = j, obstacle.y = (14 + i));
   }
  }
}

void hard(){

set_obstacle();

if((ball.y == 1) || (ball.y == 31))
   directionUp = !directionUp;
if(ball.x == 0)
{
   directionRight = !directionRight;
   scoreP2++;
   if(scoreP2 == 1)
      PORTESET = 1;
   if(scoreP2 == 2)
      PORTESET = 2;
   if(scoreP2 == 3)
      PORTESET = 4;
}

if(ball.x == 126)
{
   directionRight = !directionRight;
   scoreP1++;
   if(scoreP1 == 1)
      PORTESET = 128;
   if(scoreP1 == 2)
      PORTESET = 64;
   if(scoreP1 == 3)
      PORTESET = 32;
}

if((ball.x == paddle1.x) && (ball.y == paddle1.y) ||
   (ball.x == paddle1.x) && (ball.y == paddle1.y + 1) ||
   (ball.x == paddle1.x) && (ball.y == paddle1.y + 2) ||
   (ball.x == paddle1.x) && (ball.y == paddle1.y + 3) ||
   (ball.x == paddle1.x) && (ball.y == paddle1.y + 4) ||
   (ball.x == paddle1.x) && (ball.y == paddle1.y + 5) ||
   (ball.x == paddle1.x) && (ball.y == paddle1.y + 6) ||

   (ball.x + 1 == paddle2.x) && (ball.y == paddle2.y) ||
   (ball.x + 1 == paddle2.x) && (ball.y == paddle2.y + 1) ||
   (ball.x + 1 == paddle2.x) && (ball.y == paddle2.y + 2) ||
   (ball.x + 1 == paddle2.x) && (ball.y == paddle2.y + 3) ||
   (ball.x + 1 == paddle2.x) && (ball.y == paddle2.y + 4) ||
   (ball.x + 1 == paddle2.x) && (ball.y == paddle2.y + 5) ||
   (ball.x + 1 == paddle2.x) && (ball.y == paddle2.y + 6)||

   (ball.x + 1 == 61 ) && (ball.y == 6) ||
   (ball.x + 1 == 61) && (ball.y == 7) ||
   (ball.x + 1 == 61) && (ball.y == 8) ||
   (ball.x + 1 == 61) && (ball.y == 9) ||
   (ball.x + 1 == 61) && (ball.y == 10) ||
   (ball.x + 1 == 61) && (ball.y == 11) ||
   (ball.x + 1 == 61) && (ball.y == 12)||
   (ball.x + 1 == 61) && (ball.y == 13) ||

   (ball.x == 62 ) && (ball.y == 20) ||
   (ball.x == 62) && (ball.y == 21) ||
   (ball.x == 62) && (ball.y == 22) ||
   (ball.x == 62) && (ball.y == 23) ||
   (ball.x == 62) && (ball.y == 24) ||
   (ball.x == 62) && (ball.y == 25) ||
   (ball.x == 62) && (ball.y == 26) ||
   (ball.x == 62) && (ball.y == 27))

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
   paddle1.y = 13;
   paddle1.x = 1;
   paddle1.speed = 10;
   paddle1.score = 0;

   //Initialize player 2 paddle
   paddle2.x = 126;
   paddle2.y = 13;
   paddle2.speed = 10;
   paddle2.score = 0;

   //Set startpoint for ball and paddles
   set_ball(ball);
   set_paddle(paddle1);
   set_paddle(paddle2);
   update_screen();

   while(1)
   {
      //Everytime we move the paddles and ball we need to remove
      //the old positions of the ball and paddles
      clear_screen();

      //After removing the old stuff move ball and check if
      //any button is pressed to move the paddles

      btns = getbtns();
      if(getsw() & 0x2)           //Medium
       def = 0xffff;

      if(btns & (getsw() & 0x8))
         move_paddle(btns);

      if((getsw() & 0x8) == 0)        //Singleplayer
      single_palyer(btns);
      else
      move_paddle(btns);

       if(getsw() & 0x4)              //Hard
       {
        def = 0xf000;
        hard();
       }
       else
        move_ball();

      set_ball(ball);
      set_paddle(paddle1);
      set_paddle(paddle2);




      //Small delay to make game move smooth without having
      //to use timers or such
      int i;
      for(i = 0; i < def; i++);

      //After everything is done update the screen
      update_screen();

      //After updating the screen check if game is over and who won
      if(scoreP1 == 3)
      {
         winner = 1;
         break;
      }
      if(scoreP2 == 3)
      {
         winner = 2;
         break;
      }
   }
}
