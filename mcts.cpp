#include <iostream>
#include <utility>
#include <math.h>
#include <queue>
#include <algorithm>
#include <climits>
#include "mcts.h"
#include "board.h"
#include "heuristic.h"
using namespace std;

class myComparator {
  public:
    bool operator() (pair<int, pair<int, int>> &p1, pair<int, pair<int, int>> &p2) {
      return p1.first < p2.first;
    }
};

MCTS::MCTS(Node* r, int n, int s, int c, int ex){
	root = r;
    nodesToExpand = n;
    simulationLimit = s;
    expansionConstraint = c;
    expansionType = ex;
}

vector<pair<int, int>> Node::ExpansionHeuristic(int color, int n){
    // cout<<"Node::ExpansionHeuristic\n";
    vector<pair<int, int>> moves;
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, myComparator> pq;
    for(int row = 0; row<15; row++){
        for(int col=0;col<15;col++){
            if(board[row][col] == 0){
                int wt = 0;
                int w, b = 0;
                w = playerWhiteWeightage[row][col];
                b = playerBlackWeightage[row][col];
                wt = w + b;
                pq.push(make_pair(wt, make_pair(row, col)));
            }
        }
    }
    int posWt = 0;
    while(pq.size()){
        if(pq.top().first > 0){
            posWt++;
        }
        moves.push_back(pq.top().second);
        if(moves.size() >= n){
            return moves;
        }
        pq.pop();
    }
    random_shuffle(moves.begin() + posWt, moves.end());
    return moves;
}

void Node::CalculateWts(int color){
    bool player = (color == black);
    CalculateWeights(board, playerBlackWeightage, black, player);
    CalculateWeights(board, playerWhiteWeightage, white, !player);
}

void MCTS::NextBestMove(int *pos, int color){
    // cout<<"MCTS::NextBestMove: "<<color<<endl;
    Node* now = NULL;
    Node* next = NULL;
    int numberOfSimulations = 0;
    root->CalculateWts(color);
    // root->PrintWeights();
    while(numberOfSimulations < simulationLimit){
        now = next = root;
        do {
            now = next;
            next = now->BestChildWithUCB();
        } while (next != NULL);
        if(now->Simulations() > expansionConstraint){
            vector<pair<int, int>> moves;
            if(expansionType == randomExpansion){
                moves = now->AvailableMoves();
                random_shuffle(moves.begin(), moves.end());
            }
            if(expansionType == weightedExpansion){
                moves = now->ExpansionHeuristic(color, 225);
            }
            now->Expand(nodesToExpand, color, moves);
            now = now->RandomChild();
        }
        if(now != NULL){
            now->BackPropogate(now->Simulate(color, weightedExpansion));
        }
        
        numberOfSimulations++;
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

void Node::Expand(int noOfMoves, int color, vector<pair<int, int>> moves){
    // cout<<"Node::Expand: "<<moves.size()<<endl;

    int i = 0;
    while(i < moves.size()){
        if(i > noOfMoves){
            break;
        }
        pair<int, int> move = moves[i];
        Node* child = new Node(board);
        child->MakeMove(move.first, move.second, color); 
        child->SetParent(this);
        child->SetLevel(this->Level() + 1);
        child->CalculateWts(color);
        this->children.push_back(child);

        i++;
    }
}

int Node::Simulate(int color, int type){
    // cout<<"Node::Simulate: "<<color<<endl;
    int player = color;
    Node* tempNode = new Node(board);
    vector<pair<int, int>> moves;
    if(type == randomExpansion){
        moves = AvailableMoves();
        random_shuffle(moves.begin(), moves.end());
        for(int itr = 0; itr < moves.size(); itr++){
            pair<int, int> move = moves[itr];
            tempNode->MakeMove(move.first, move.second, player);
        
            if(!ContinuePlaying(player)){
                break;
            }
        
            player = player%2 + 1;
        }
    }
    int counter = 0;
    if(type == weightedExpansion){
        int b[15][15], w[15][15];
        tempNode->SetWeigths(playerBlackWeightage, playerWhiteWeightage);
        tempNode->CalculateWts(color);
        moves = ExpansionHeuristic(color, 225);
        while(moves.size() > 0){
            pair<int, int> move = moves[0];
            moves.pop_back();

            tempNode->MakeMove(move.first, move.second, player);
            if(!ContinuePlaying(player)){
                break;
            }

            // if(counter % 50 == 0){
            //     int b[15][15], w[15][15];
            //     tempNode->SetWeigths(b, w);
            //     tempNode->CalculateWts(color);
            //     moves = tempNode->ExpansionHeuristic(player, 225);
            //     random_shuffle(moves.begin(), moves.end());
            // }
            
            player = player%2 + 1;
            counter++;
        }
    }
    int win = checkBoardStatus(board);
    if(win == 0){
        return 0;
    }
    if(win == color){
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
            playerWhiteWeightage[i][j] = playerBlackWeightage[i][j] = 0;
		}
	}
    
    wins = 0;
    simulations = 0;
    parent = NULL;
    moveRow = -1;
    moveCol = -1;
    level = 0;
}

void Node::SetWeigths(int b[15][15], int w[15][15]){
    for (int i=0; i<15;i++){
		for(int j=0;j<15;j++){
            playerWhiteWeightage[i][j] = w[i][j];
            playerBlackWeightage[i][j] = b[i][j];
		}
	}
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
    if(wins>0){
    cout<<"Level: "<<level<<", color: "<<color<<", (w: "<<wins<<", s: "<<simulations<<")"<<endl;
    }
}

void Node::PrintWeights(){
    for (int i = 0; i <15; i++){
        cout<<"-------------------------------------------------------------"<<endl;
        for (int j = 0; j < 15; j++){
            cout<<"|"<<playerBlackWeightage[i][j]<<","<<playerWhiteWeightage[i][j];
        }
        cout<<"|"<<endl;
    }
    cout<<"-------------------------------------------------------------"<<endl;
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
    return float(nodeWins)/float(nodeSimulations) + sqrt(float(2 * log(totalSimulations))/float(nodeSimulations));
}