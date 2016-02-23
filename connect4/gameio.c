#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "gameio.h"
#include "logic.h"

int numPlayers()
 {
 int p = 0;
 while ((p != 1)&&(p != 2))
  {
  printf("Number of players? (1-2): ");
  scanf("%d",&p);
  }
 return p;
 }

Board *
createBoard(int x,int y)
 {
 int r,c = 0;
 Board *b = malloc(sizeof(Board));
 b->cols = x;
 b->rows = y;
 b->slots = malloc(sizeof(int *) * y);
 for (r = 0; r < y; ++r)
  {
  b->slots[r] = malloc(sizeof(int) * x);
  for (c = 0; c < x; ++c)
   b->slots[r][c] = 0;
  }
 return b;
 }

void
dispBoard(Board *b)
 {
 int r,c = 0;
 for (r = 0; r < b->rows; ++r)
  {
  for (c = 0; c < b->cols; ++c)
   {
   if (b->slots[r][c] == 1)
    printf("[X] ");
   else if (b->slots[r][c] == 2)
    printf("[O] ");
   else
    printf("[ ] ");
   }
  printf("\n");
  }
 for (c = 0; c < b->cols; ++c)
  printf("----");
 printf("\n");
 for (c = 0; c < b->cols; ++c)
  printf("(%d) ",c + 1);
 printf("\n");
 return;
 }

int playerMove(Board *b,int p)
 {
 int m = 0;
 while ((m < 1)||(m > b->cols))
  {
  printf("Enter Player %d's move: ",p);
  scanf("%d",&m);
  }
 printf("\n");
 return m - 1;
 }

int playerWin(int p)
 {
 int go = 1;
 printf("CONGRATULATIONS\n");
 printf("PLAYER %d WON\n",p);
 return go;
 }
