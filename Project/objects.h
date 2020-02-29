/* Code written by eschmar (github)
** 2016
*/
#ifndef TYPES_H_
#define TYPES_H_

typedef struct Paddle
{
   short x, y, speed, score;
} Paddle;

typedef struct Ball
{
   short x, y, speedX, speedY;
} Ball;

typedef struct Obsticle
{
   short x, y;
} Obsticle;

#endif //TYPES_H_
