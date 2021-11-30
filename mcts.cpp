#include <iostream>
#include <math.h>
#include "mcts.h"
using namespace std;

void SetBoard(Node* n, int b[15][15]){
	for (int i=0; i<15;i++){
		for(int j=0;j<15;j++){
			n->board[i][j] = b[i][j];
		}
	}
}

void SetParent(struct Node* n, Node* p){
	n->parent = p;
}

void AddChild(Node* n, Node* c){
	n->children.push_back(c);
}

void PrintBoard(Node* n){
    for (int i = 0; i <15; i++){
        cout<<"-------------------------------------------------------------"<<endl;
        for (int j = 0; j < 15; j++){
            cout<<"| "<<n->board[i][j]<<" ";
        }
        cout<<"|"<<endl;
    }
    cout<<"-------------------------------------------------------------"<<endl;
}

float UCB(int wins, int simulations, int totalSimulations){
    return float(wins/simulations) + sqrt(log(totalSimulations)/simulations);
}