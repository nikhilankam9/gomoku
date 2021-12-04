#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <chrono>
#include "board.h"
#include "mcts.h"
using namespace std;
using namespace std::chrono;

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

string toString(int color){
    if(color == white){
        return "White";
    }
    if(color == black){
        return "Black";
    }
    return "";
}

void play(int board[15][15], int color, int position[2]){
    board[position[0]][position[1]] = color;
}

namespace Nikhil{
    void search_old(int board[15][15], int color, int position[2]){
        auto start = high_resolution_clock::now();

        MCTS *tree = new MCTS(new Node(board), 16, 3000, -1, weightedExpansion);
        tree->NextBestMove(position, color);

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        cout<<"Time taken: "<<duration.count()<<endl;
    }

    void search(int board[15][15], int color, int position[2]){
        search_old(board, color + 1, position);
    }
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
    cout<<endl;
}

int main() {
    cout << "Welcome to GOMOKU, PLAY!!\n";

    int board[15][15] = {0};
    int playerTurn = 0; // even = Black's turn and odd = White's turn
    int plays = 1;
    int position[2];

    board[7][7] = 1;
    playerTurn = 1;

    while (plays <= 225){
        display(board);

        // //Human vs Computer
        // if(playerTurn%2 == 0){
        //     cout<<toString(playerTurn%2 + 1)<<" turn: Enter position (i, j) where 1<=i,j<=15\n";
        //     cin>>position[0]>>position[1];
        //     position[0]--; 
        //     position[1]--;
        //     play(board, playerTurn%2 + 1, position);
        // }else{
        //     position[0] = position[1] = -1;
        //     Nikhil::search(board, playerTurn%2 +1, position);
        //     if(position[0] == -1 || position[1] == -1){
        //         cout<<"Tie!!"<<endl;
        //         display(board);
        //     }
        //     cout<<plays<<"- "<<toString(playerTurn%2 + 1)<<":("<<position[0]+1<<","<<position[1]+1<<")"<<endl;

        //     play(board, playerTurn%2 + 1, position);
        // }

        // //Human vs Human
        // position[0] = position[1] = -1;
        // cout<<toString(playerTurn%2 + 1)<<" turn: Enter position (i, j) where 1<=i,j<=15\n";
        // cin>>position[0]>>position[1];
        // position[0]--;
        // position[1]--;
        // if(!validMove(board, playerTurn%2 + 1, position)){
        //     continue;
        // }
        // play(board, playerTurn%2 + 1, position);

        // Computer vs Computer
        Nikhil::search(board, playerTurn%2 +1 - 1, position);
        if(position[0] == -1 || position[1] == -1){
            cout<<"Tie!!"<<endl;
            display(board);
        }
        cout<<plays<<"- "<<toString(playerTurn%2 + 1)<<":("<<position[0]+1<<","<<position[1]+1<<")"<<endl;
        play(board, playerTurn%2 + 1, position);

        //Common
        int status = checkBoardStatus(board);
        if (status == black || status == white){
            cout<<"Winner!!: "<<toString(status)<<endl;
            break;
        }

        playerTurn++;
        plays++;
    }
    display(board);
    return 0;
}