#ifndef HEURISTIC_H
#define HEURISTIC_H
#include <vector>
using namespace std;

void CalculateWeights(int board[15][15], int weights[15][15], int color);
void CalculateHorizontal(int board[15][15], int weights[15][15], int color);
void CalculateVertical(int board[15][15], int weights[15][15], int color);
void CalculateDiagonalBack(int board[15][15], int weights[15][15], int color);
void CalculateDiagonalForward(int board[15][15], int weights[15][15], int color);

vector<pair<int, int>> HorizontalPatterns(int board[15][15], int color, int row);
vector<pair<int, int>> VerticalPatterns(int board[15][15], int color, int col);
vector<pair<pair<int, int>, int>> DiagonalPatternsBackSlash(int board[15][15], int color, int row, int col);
vector<pair<pair<int, int>, int>> DiagonalPatternsForwardSlash(int board[15][15], int color, int row, int col);


#endif