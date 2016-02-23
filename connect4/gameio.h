typedef struct board
 {
 int **slots;
 int cols;
 int rows;
 } Board;
int numPlayers();
Board *createBoard(int x,int y);
void dispBoard(Board *b);
int playerMove(Board *b,int p);
int playerWin(int p);
