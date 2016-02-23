#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "gameio.h"
#include "logic.h"

int main(int argc,char **argv)
 {
 int gameOver = 0;
 int move = 0;
 int player = 2;
 int players = 1;
 int valid = 0;
 int pieces = atoi(argv[3]);
 printf("Welcome to Connect 4 or More!\n\n");
 printf("New Game\n");
 players = numPlayers();
 Board *b;
 b = createBoard(atoi(argv[1]),atoi(argv[2]));
 dispBoard(b);
 while (gameOver == 0)
  {
  valid = 0;
  if (player == 1)
   player = 2;
  else
   player = 1;
  while (valid == 0)
   {
   if ((player == 1)||((player == 2)&&(players == 2)))
    move = playerMove(b,player);
   if ((player == 2)&&(players == 1))
    move = computerMove(b,player);
   valid = legalMove(b,move);
   if (1 == valid)
    playerPlace(b,move,player);
   }
  dispBoard(b);
  if (check(b,player,pieces) != 0)
   gameOver = playerWin(check(b,player,pieces));
  if (movesLeft(b) == 0)
   gameOver = 1;
  }
 printf("Game Over\n");
 return 0;
 }
