#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "board.h"
#include "mcts.h"
using namespace std;

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
    Node *n = new Node();
    SetBoard(n, board);
    PrintBoard(n);
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

    int count = 0;

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

        count++;
        if(count>1){
            break;
        }
    }
    
    int pos[2];
    search(board, 1, pos);
    return 0;
}