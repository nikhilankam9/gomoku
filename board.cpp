#include <vector>
#include "board.h"
using namespace std;

bool checkHorizontal(int board[15][15], int color, int row){
    int j = 0;
    int count = 0;
    while(j < 14){
        if(board[row][j] == color){
            int found = 1;
            for(int k=1; k< 5; k++){
                if(j+k< 15){
                    if(board[row][j+k] != color){
                        j = j + k;
                        break;
                    }
                    found++;
                }
            }
            if(found == 5){
                return true;
            }
        }
        j++;
    }
    return false;
}

bool checkVertical(int board[15][15], int color, int col){
    int j = 0;
    int count = 0;
    while(j < 14){
        if(board[j][col] == color){
            int found = 1;
            for(int k=1; k< 5; k++){
                if(j+k< 15){
                    if(board[j+k][col] != color){
                        j = j + k;
                        break;
                    }
                    found++;
                }
            }
            if(found == 5){
                return true;
            }
        }
        j++;
    }
    return false;
}

int checkDiagonal_1(int board[15][15], int color, int row, int col){
    int i = row, j = col;
    while(i<15 && j< 15){
        if(board[i][j] == color){
            int found = 1;
            for(int k=1;k<5;k++){
                if(i+k<15 && j+k<15){
                    if(board[i+k][j+k] != color){
                        i = i+k;
                        j = j+k;
                        break;
                    }
                    found++;
                }
            }
            if(found == 5){
                return true;
            }
        }
        i++;
        j++;
    }
    return false;
}

int checkDiagonal_2(int board[15][15], int color, int row, int col){
    int i = row, j = col;
    while(i<15 && j>=0){
        if(board[i][j] == color){
            int found = 1;
            for(int k=1;k<5;k++){
                if(i+k<15 && j-k>=0){
                    if(board[i+k][j-k] != color){
                        i = i+k;
                        j = j-k;
                        break;
                    }
                    found++;
                }
            }
            if(found == 5){
                return true;
            }
        }
        i++;
        j--;
    }
    return false;
}

int checkBoardStatus(int board[15][15]){
    vector<int> players;
    players.push_back(black);
    players.push_back(white);

    for(auto p: players){
        for (int i=0;i<15;i++){
            if(checkHorizontal(board, p, i)){
                return p;
            }
            if(checkVertical(board, p, i)){
                return p;
            }
            if(checkDiagonal_1(board, p, 0, i)){
                return p;
            }
            if(checkDiagonal_1(board, p, i, 0)){
                return p;
            }
            if(checkDiagonal_2(board, p, 0, i)){
                return p;
            }
            if(checkDiagonal_2(board, p, i, 14)){
                return p;
            }
        }
    }
    return 0;
}