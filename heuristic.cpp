#include <iostream>
#include <vector>
#include "heuristic.h"
using namespace std;

void CalculateWeights(int board[15][15], int weights[15][15], int color){
    CalculateHorizontal(board, weights, color);
    CalculateVertical(board, weights, color);
    CalculateDiagonalBack(board, weights, color);
    CalculateDiagonalForward(board, weights, color);
}

void CalculateHorizontal(int board[15][15], int weights[15][15], int color){
    for(int row=0; row< 15; row++){
        for(auto p: HorizontalPatterns(board, color, row)){
            int inRow = p.second - p.first + 1;

            bool leftClosed = true, rightClosed = true;
            if(p.first - 1 > 0 && board[row][p.first - 1] == 0){
                leftClosed = false;
            }
            if(p.second + 1 < 15 && board[row][p.second + 1] == 0){
                rightClosed = false;
            }

            int multiplier = int(!leftClosed + !rightClosed);
            if(!leftClosed){
                weights[row][p.first - 1] += inRow * multiplier;
            }
            if(!rightClosed){
                weights[row][p.second + 1] += inRow * multiplier;
            }
        }
    }
}

void CalculateVertical(int board[15][15], int weights[15][15], int color){
    for(int col=0; col< 15; col++){
        for(auto p: VerticalPatterns(board, color, col)){
            int inRow = p.second - p.first + 1;

            bool topClosed = true, bottomClosed = true;
            if(p.first - 1 > 0 && board[p.first - 1][col] == 0){
                topClosed = false;
            }
            if(p.second + 1 < 15 && board[p.second + 1][col] == 0){
                bottomClosed = false;
            }

            int multiplier = int(!topClosed + !bottomClosed);
            if(!topClosed){
                weights[p.first - 1][col] += inRow * multiplier;
            }
            if(!bottomClosed){
                weights[p.second + 1][col] += inRow * multiplier;
            }
        }
    }
}

void CalculateDiagonalBack(int board[15][15], int weights[15][15], int color){
    for(int c=0; c< 15; c++){
        for(auto p: DiagonalPatternsBackSlash(board, color, 0, c)){
            int inRow = p.second;

            bool topClosed = true, bottomClosed = true;
            if(p.first.first - 1 > 0 && p.first.second - 1 > 0 && board[p.first.first - 1][p.first.second - 1] == 0){
                topClosed = false;
            }
            if(p.first.first + p.second < 15 && p.first.second + p.second < 15 && board[p.first.first + p.second][p.first.second + p.second] == 0){
                bottomClosed = false;
            }

            int multiplier = int(!topClosed + !bottomClosed);
            if(!topClosed){
                weights[p.first.first - 1][p.first.second - 1] += inRow * multiplier;
            }
            if(!bottomClosed){
                weights[p.first.first + p.second][p.first.second + p.second] += inRow * multiplier;
            }
        }
        if(c != 0){
            for(auto p: DiagonalPatternsBackSlash(board, color, c, 0)){
                int inRow = p.second;

                bool topClosed = true, bottomClosed = true;
                if(p.first.first - 1 > 0 && p.first.second - 1 > 0 && board[p.first.first - 1][p.first.second - 1] == 0){
                    topClosed = false;
                }
                if(p.first.first + p.second < 15 && p.first.second + p.second < 15 && board[p.first.first + p.second][p.first.second + p.second] == 0){
                    bottomClosed = false;
                }

                int multiplier = int(!topClosed + !bottomClosed);
                if(!topClosed){
                    weights[p.first.first - 1][p.first.second - 1] += inRow * multiplier;
                }
                if(!bottomClosed){
                    weights[p.first.first + p.second][p.first.second + p.second] += inRow * multiplier;
                }
            }
        }
    }
}

void CalculateDiagonalForward(int board[15][15], int weights[15][15], int color){
    for(int c=0; c< 15; c++){
        for(auto p: DiagonalPatternsForwardSlash(board, color, 0, c)){
            int inRow = p.second;

            bool topClosed = true, bottomClosed = true;
            if(p.first.first - 1 > 0 && p.first.second + 1 < 15 && board[p.first.first - 1][p.first.second + 1] == 0){
                topClosed = false;
            }
            if(p.first.first + p.second < 15 && p.first.second - p.second > 0 && board[p.first.first + p.second][p.first.second - p.second] == 0){
                bottomClosed = false;
            }

            int multiplier = int(!topClosed + !bottomClosed);
            if(!topClosed){
                weights[p.first.first - 1][p.first.second + 1] += inRow * multiplier;
            }
            if(!bottomClosed){
                weights[p.first.first + p.second][p.first.second - p.second] += inRow * multiplier;
            }
        }
        if(c != 0){
            for(auto p: DiagonalPatternsForwardSlash(board, color, c, 14)){
                int inRow = p.second;

                bool topClosed = true, bottomClosed = true;
                if(p.first.first - 1 > 0 && p.first.second + 1 < 15 && board[p.first.first - 1][p.first.second + 1] == 0){
                    topClosed = false;
                }
                if(p.first.first + p.second < 15 && p.first.second - p.second > 0 && board[p.first.first + p.second][p.first.second - p.second] == 0){
                    bottomClosed = false;
                }

                int multiplier = int(!topClosed + !bottomClosed);
                if(!topClosed){
                    weights[p.first.first - 1][p.first.second + 1] += inRow * multiplier;
                }
                if(!bottomClosed){
                    weights[p.first.first + p.second][p.first.second - p.second] += inRow * multiplier;
                }
            }
        }
    }
}

vector<pair<int, int>> HorizontalPatterns(int board[15][15], int color, int row){
    vector<pair<int, int>> result;
    int i = 0, j;
    while(i < 15){
        if(board[row][i] == color){
            j = i;
            while(j < 15){
                if(board[row][j] == color){
                    j++;
                }else{
                    break;
                }
            }
            result.push_back(make_pair(i, j-1));
            i = j -1;
        }
        i++;
    }
    return result;
}

vector<pair<int, int>> VerticalPatterns(int board[15][15], int color, int col){
    vector<pair<int, int>> result;
    int i = 0, j;
    while(i < 15){
        if(board[i][col] == color){
            j = i;
            while(j < 15){
                if(board[j][col] == color){
                    j++;
                }else{
                    break;
                }
            }
            result.push_back(make_pair(i, j-1));
            i = j -1;
        }
        i++;
    }
    return result;
}

vector<pair<pair<int, int>, int>> DiagonalPatternsBackSlash(int board[15][15], int color, int row, int col){
    vector<pair<pair<int, int>, int>> result;
    int i = row, j = col;
    int k = 0;
    while(i < 15 && j < 15){
        if(board[i][j] == color){
            while(i+k<15 && j+k < 15){
                if(board[i+k][j+k] == color){
                    k++;
                }else{
                    break;
                }
            }
            result.push_back(make_pair(make_pair(i, j), k));
            i = i + k - 1;
            j = j + k - 1;
            k = 0;
        }
        i++;
        j++;
    }
    return result;
}

vector<pair<pair<int, int>, int>> DiagonalPatternsForwardSlash(int board[15][15], int color, int row, int col){
    vector<pair<pair<int, int>, int>> result;
    int i = row, j = col;
    int k = 0;
    while(i < 15 && j >= 0){
        if(board[i][j] == color){
            while(i+k<15 && j-k >= 0){
                if(board[i+k][j-k] == color){
                    k++;
                }else{
                    break;
                }
            }
            result.push_back(make_pair(make_pair(i, j), k));
            i = i + k - 1;
            j = j - k + 1;
            k = 0;
        }
        i++;
        j--;
    }
    return result;
}