#ifndef MCTS_H
#define MCTS_H
#include <vector>
using namespace std;

struct Node {
	int board[15][15];
	struct Node* parent;
	vector<Node*> children;
};

void SetBoard(Node* n, int b[15][15]);
void SetParent(Node* n, Node* p);
void AddChild(Node* n, Node* c);
void PrintBoard(Node* n);

float UCB(int wins, int simulations, int totalSimulations);

#endif