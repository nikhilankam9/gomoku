#ifndef BOARD_H
#define BOARD_H

const int black = 1;
const int white = 2;

bool checkHorizontal(int board[15][15], int color, int row);
bool checkVertical(int board[15][15], int color, int col);
int checkDiagonal_1(int board[15][15], int color, int row, int col);
int checkDiagonal_2(int board[15][15], int color, int row, int col);
int checkBoardStatus(int board[15][15]);

#endif