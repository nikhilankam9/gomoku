#include <iostream>
#include <string>
#include<algorithm>
using namespace std;

const int black = 1;
const int white = 2;

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
    for (int i=0;i<15;i++){
        if(checkHorizontal(board, black, i)){
            return black;
        }
        if(checkHorizontal(board, white, i)){
            return white;
        }
        if(checkVertical(board, black, i)){
            return black;
        }
        if(checkVertical(board, white, i)){
            return white;
        }
        if(checkDiagonal_1(board, black, 0, i)){
            return black;
        }
        if(checkDiagonal_1(board, white, 0, i)){
            return white;
        }
        if(checkDiagonal_1(board, black, i, 0)){
            return black;
        }
        if(checkDiagonal_1(board, white, i, 0)){
            return white;
        }
        if(checkDiagonal_2(board, black, 0, i)){
            return black;
        }
        if(checkDiagonal_2(board, white, 0, i)){
            return white;
        }
        if(checkDiagonal_2(board, black, i, 14)){
            return black;
        }
        if(checkDiagonal_2(board, white, i, 14)){
            return white;
        }
    }
    return 0;
}

bool validMove(int board[15][15], int color, int position[2]){
    if(position[0] < 0 || position[0] > 14){
        cout<<"Cannot make move!, wrong position[0].\n";
        return false;
    }
    if(position[1] < 0 || position[1] > 14){
        cout<<"Cannot make move!, wrong position[1].\n";
        return false;
    }
    if(board[position[0]][position[1]] != 0){
        cout<<"Cannot make move!, already occupied.\n";
        return false;
    }
    if(color != white && color != black){
        cout<<"Cannot make move!, wrong color: "<<color<<endl;
        return false;
    }
    return true;
}

void play(int board[15][15], int color, int position[2]){
    board[position[0]][position[1]] = color;
}

void search(int board[15][15], int color, int position[2]){
    cout<<"searching the board\n";
}

void display(int board[15][15]){
    for (int i = 0; i <15; i++){
        cout<<"-------------------------------------------------------------"<<endl;
        for (int j = 0; j < 15; j++){
            cout<<"| "<<board[i][j]<<" ";
        }
        cout<<"|"<<endl;
    }
    cout<<"-------------------------------------------------------------"<<endl;
}

string toString(int color){
    if(color == white){
        return "White";
    }
    if(color == black){
        return "Black";
    }
    return "";
}

int main() {
    cout << "Welcome to GOMOKU, PLAY!!\n";

    int board[15][15] = {0};
    int playerTurn = 0; // even = Black's turn and odd = White's turn

    while (true){
        int position[2];
        cout<<toString(playerTurn%2 + 1)<<" turn: Enter position (i, j) where 1<=i,j<=15\n";
        cin>>position[0]>>position[1];
        position[0]--;
        position[1]--;

        if(!validMove(board, playerTurn%2 + 1, position)){
            continue;
        }

        play(board, playerTurn%2 + 1, position);

        int status = checkBoardStatus(board);
        if (status == black || status == white){
            cout<<"Winner!!: "<<toString(status)<<endl;
            break;
        }
        display(board);

        //TODO end condition when no more moves possible
        playerTurn++;
        cout<<endl;
    }
    
    display(board);
    return 0;
}

