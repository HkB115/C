#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "gameio.h"
#include "logic.h"

int legalMove(Board *b,int m)
 {
 int temp;
 if (b->slots[0][m] != 0)
  temp = 0;
 else
  temp = 1;
 return temp;
 }

void playerPlace(Board *b,int m,int p)
 {
 int r;
 for(r = 0; r <= b->rows - 1; ++r)
  {
  if ((b->slots[b->rows - 1 - r][m] == 0))
   {
   b->slots[b->rows - 1 - r][m] = p;
   return;
   }
  }
 if (b->slots[b->rows - 1][m] == 0)
 b->slots[b->rows - 1][m] = p;
 return;
 }

int computerMove(Board *b,int p)
 {
 int m = 0;
 m = rand() % b->cols - 1;
 printf("\n");
 return m - 1;
 }

int movesLeft(Board *b)
 {
 int c;
 int m = 0;
 for (c = 0; c < b->cols; ++c)
  {
  if (b->slots[0][c] == 0)
   m = 1;
  }
 return m;
 }

int check(Board *b,int p,int n)
 {
 int c,r,i;
 int count = 0;
 for (r = 0; r < (b->rows); ++r)
  for (c = 0; c < (b->cols - n); ++c)
   {
   count = 0;
   for (i = 0; i < n; ++i)
    if (b->slots[r][c + i] == p)
     ++count;
   if (count == n)
    return p;
   }
 for (c = 0; c < (b->cols); ++c)
  for (r = 0; r < (b->rows - n); ++r)
   {
   count = 0;
   for (i = 0; i < n; ++i)
    if (b->slots[r + i][c] == p)
     ++count;
   if (count == n)
    return p;
   }
 for (r = 0; r < (b->rows - n); ++r)
  for (c = 0; c < (b->cols - n); ++c)
   {
   count = 0;
   for (i = 0; i < n; ++i)
    if (b->slots[r + i][c + i] == p)
     ++count;
   if (count == n)
    return p;
   }
 for (r = 0; r < (b->rows - n); ++r)
  for (c = b->cols - 1; c > n - 1; --c)
   {
   count = 0;
   for (i = 0; i < n; ++i)
    if (b->slots[r + i][c - i] == p)
     ++count;
   if (count == n)
    return p;
   }
 return 0;
 }
