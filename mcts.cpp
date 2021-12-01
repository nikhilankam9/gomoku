#include <iostream>
#include <utility>
#include <math.h>
#include <queue>
#include <climits>
#include "mcts.h"
#include "board.h"
using namespace std;


MCTS::MCTS(Node* r){
	root = r;
}

void MCTS::NextBestMove(int *pos, int color){
    // cout<<"MCTS::NextBestMove: "<<color<<endl;
    Node* now = NULL;
    Node* next = NULL;
    int count = 0;
    while(count<1000){
        now = next = root;
        do {
            now = next;
            next = now->BestChildWithUCB();
        } while (next != NULL);
        now->Expand(20, color);
        now = now->RandomChild();
        if(now == NULL){
            cout<<"NULL pointer"<<endl;
        }
        now->BackPropogate(now->Simulate(color));
        
        count++;
    }

    next = root->BestChildWithUCB();
    if(next != NULL){
        pos[0] = next->MoveRow();
        pos[1] = next->MoveColumn();
    }

    // this->PrintTree();
}

Node* Node::BestChildWithUCB(){
    int totalSims = simulations;
    float maxUCB = -1.0;
    int bestChildIndex = -1;
    for(int i=0;i<children.size();i++){
        float currUCB = UCB(children[i]->Wins(), children[i]->Simulations(), simulations);
        if(maxUCB < currUCB){
            maxUCB = currUCB;
            bestChildIndex = i;
        }
    }

    if (bestChildIndex == -1){
        return RandomChild();
    }
    // cout<<"Node::BestChildWithUCB: "<<bestChildIndex<<endl;
    return children[bestChildIndex];
}

Node* Node::RandomChild(){
    int noChild = children.size();
    if(noChild == 0){
        return NULL;
    }
    int randInd = rand() % noChild;
    // cout<<"Node::RandomChild: "<<randInd<<endl;
    return children[randInd];
}

void Node::Expand(int noOfMoves, int color){
    vector<pair<int, int>> moves = AvailableMoves();
    int availableMoves = moves.size();
    if(noOfMoves == -1){
        noOfMoves = availableMoves;
    }
    // cout<<"Node::Expand: ("<<noOfMoves<<", "<<availableMoves<<")"<<endl;
    while(noOfMoves--){
        int moveIndex = rand() % availableMoves;
        pair<int, int> move = moves[moveIndex];
        Node* child = new Node(board);
        child->MakeMove(move.first, move.second, color); 
        child->SetParent(this);
        child->SetLevel(this->Level() + 1);
        this->children.push_back(child);

        //Ignoring the currently made move
        moves[moveIndex] = moves[availableMoves-1];
        availableMoves--;
    }
}

int Node::Simulate(int color){
    vector<pair<int, int>> moves = AvailableMoves();
    int availableMoves = moves.size();
    int player = color;
    // cout<<"Node::Simulate: "<<availableMoves<<", "<<color<<endl;
    Node* tempNode = new Node(board);
    int totalMoves = availableMoves;
    while(totalMoves--){
        int moveIndex = rand() % availableMoves;
        pair<int, int> move = moves[moveIndex];
        tempNode->MakeMove(move.first, move.second, player);
        
        if(!ContinuePlaying(player)){
            break;
        }
        
        player = player%2 + 1;
        //Ignoring the currently made move
        moves[moveIndex] = moves[availableMoves-1];
        availableMoves--;
    }
    if(checkBoardStatus(board) == color){
        return 1;
    }
    return 0;
}

void Node::BackPropogate(int val){
    // cout<<"Node::BackPropogate"<<endl;
    Node* crawl = this;
    while(crawl != NULL) {
        crawl->UpdateWins(val);
        crawl->UpdateSimulations(1);
        crawl = crawl->parent;
    }
}

Node::Node(int b[15][15]){
    for (int i=0; i<15;i++){
		for(int j=0;j<15;j++){
			board[i][j] = b[i][j];
		}
	}

    wins = 0;
    simulations = 0;
    parent = NULL;
    moveRow = -1;
    moveCol = -1;
    level = 0;
}

void MCTS::PrintTree(){
    queue<Node*> q;
    q.push(root);
    while(q.size()>0){
        Node* curr = q.front();
        q.pop();
        curr->PrintNode();
        for(auto c :curr->Children()){
            q.push(c);
        }
        if(curr->Level()==2){
            break;
        }
    }
}

void Node::PrintNode(){
    cout<<"Level: "<<level<<", color: "<<color<<", (w: "<<wins<<", s: "<<simulations<<")"<<endl;
}

bool Node::ContinuePlaying(int color){
    int winner = checkBoardStatus(board);
    if(winner == 0){
        return true;
    }
    return false;
}

void Node::MakeMove(int row, int col, int c){
    board[row][col] = c;
    moveRow = row;
    moveCol = col;
    color = c;
}

int Node::MoveRow(){
    return moveRow;
}

int Node::MoveColumn(){
    return moveCol;
}

vector<pair<int, int>> Node::AvailableMoves(){
    vector<pair<int, int>> moves;
    for (int i=0; i<15;i++){
		for(int j=0;j<15;j++){
			if(board[i][j] == 0){
                moves.push_back(make_pair(i, j));
            }
		}
	}
    return moves;
}

void Node::SetBoard(int b[15][15]){
	for (int i=0; i<15;i++){
		for(int j=0;j<15;j++){
			board[i][j] = b[i][j];
		}
	}
}

void Node::UpdateWins(int val){
    wins+=val;
}

void Node::UpdateSimulations(int val){
    simulations+=val;
}

void Node::SetLevel(int l){
    level = l;
}

int Node::Level(){
    return level;
}

void Node::SetColor(int c){
    color = c;
}

int Node::Color(){
    return color;
}

void Node::SetParent(Node* p){
	parent = p;
}

Node* Node::Parent(){
    return parent;
}

void Node::AddChild(Node* c){
	children.push_back(c);
}

vector<Node*> Node::Children(){
    return children;
}

int Node::Wins(){
    return wins;
}

int Node::Simulations(){
    return simulations;
}

void Node::PrintBoard(){
    for (int i = 0; i <15; i++){
        cout<<"-------------------------------------------------------------"<<endl;
        for (int j = 0; j < 15; j++){
            cout<<"| "<<board[i][j]<<" ";
        }
        cout<<"|"<<endl;
    }
    cout<<"-------------------------------------------------------------"<<endl;
}

float UCB(int nodeWins, int nodeSimulations, int totalSimulations){
    if(nodeSimulations == 0){
        return INT_MAX;
    }
    return float(nodeWins)/float(nodeSimulations) + 
        1.411 * sqrt(log(totalSimulations)/float(nodeSimulations));
}