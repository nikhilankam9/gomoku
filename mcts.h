#ifndef MCTS_H
#define MCTS_H
#include <vector>
#include <iostream>
#include <utility>
using namespace std;

const int randomExpansion = 1;

class Node {
	public:
		//Setters
		void SetBoard(int b[15][15]);
		void SetParent(Node* p);
		void UpdateWins(int val);
		void UpdateSimulations(int val);
		void AddChild(Node* c);
		void SetLevel(int l);
		void SetColor(int color);
		
		//Getters
		int Wins();
		int Simulations();
		int MoveRow();
		int MoveColumn();
		int Level();
		int Color();
		vector<Node*> Children();
		Node* Parent();

		//Misc
		Node* BestChildWithUCB();
		Node* RandomChild();
		vector<pair<int, int>> AvailableMoves();
		void Expand(int noOfMoves, int color, int type);
		void MakeMove(int row, int col, int color);
		int Simulate(int color);
		bool ContinuePlaying(int color);
		void BackPropogate(int val);
		void PrintBoard();
		void PrintNode();

		//Constructor
		Node(int b[15][15]);

	private:
		int board[15][15];
		Node* parent;
		vector<Node*> children;
		
		int wins;
		int simulations;

		int moveRow;
		int moveCol;
		int level;
		int color;
};

class MCTS{
	public:
		MCTS(Node* r, int n, int s, int c, int ex);
		void NextBestMove(int *pos, int color);
		void PrintTree();

	private:
		Node* root;
		int nodesToExpand;
		int simulationLimit;
		int expansionConstraint;

		int expansionType;
};

float UCB(int nodeWins, int nodeSimulations, int totalSimulations);

#endif