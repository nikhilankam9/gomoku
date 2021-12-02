#include <iostream>
#include <assert.h>
#include <vector>
#include "board.h"
#include "heuristic.h"
#include "util.h"

using namespace std;

int test_board[15][15] = {0};

void Test_checkHorizontal() {
    cout<<"Test_checkHorizontal:\n";
    test_board[1][1] = test_board[1][2] = test_board[1][3] = test_board[1][4] = test_board[1][5] = 1;
    assert(checkHorizontal(test_board, 1, 1) == 1);
    test_board[1][1] = test_board[1][2] = test_board[1][3] = test_board[1][4] = test_board[1][5] = 0;
    cout<<"Case1: PASSED!\n";

    test_board[1][1] = test_board[1][2] = test_board[1][4] = test_board[1][5] = test_board[1][6] = \
    test_board[1][7] = test_board[1][8] = 1;
    assert(checkHorizontal(test_board, 1, 1) == 1);
    test_board[1][1] = test_board[1][2] = test_board[1][4] = test_board[1][5] = test_board[1][6] = \
    test_board[1][7] = test_board[1][8] = 0;
    cout<<"Case2: PASSED!\n";

    test_board[1][2] = test_board[1][4] = test_board[1][5] = test_board[1][6] = test_board[1][7] = test_board[1][8] = 1;
    assert(checkHorizontal(test_board, 1, 1) == 1);
    test_board[1][2] = test_board[1][4] = test_board[1][5] = test_board[1][6] = test_board[1][7] = test_board[1][8] = 0;
    cout<<"Case3: PASSED!\n";

    test_board[1][2] = test_board[1][4] = test_board[1][5] = test_board[1][6] = test_board[1][8] = 1;
    assert(checkHorizontal(test_board, 1, 1) == 0);
    test_board[1][2] = test_board[1][4] = test_board[1][5] = test_board[1][6] = test_board[1][8] = 0;
    cout<<"Case4: PASSED!\n";

    assert(checkHorizontal(test_board, 1, 1) == 0);
    cout<<"Case5: PASSED!\n";

    cout<<endl;
}

void Test_checkVertical() {
    cout<<"Test_checkVertical\n";
    test_board[0][0] = test_board[1][0] = test_board[2][0] = test_board[3][0] = test_board[4][0] = 2;
    assert(checkVertical(test_board, 2, 0) == 1);
    test_board[0][0] = test_board[1][0] = test_board[2][0] = test_board[3][0] = test_board[4][0] = 0;
    cout<<"Case1: Passed!\n";


    test_board[0][0] = test_board[1][0] = test_board[3][0] = test_board[4][0] = test_board[5][0] = \
    test_board[6][0] = test_board[7][0] = 2;
    assert(checkVertical(test_board, 2, 0) == 1);
    test_board[0][0] = test_board[1][0] = test_board[3][0] = test_board[4][0] = test_board[5][0] = \
    test_board[6][0] = test_board[7][0] = 0;
    cout<<"Case2: Passed!\n";

    test_board[1][0] = test_board[3][0] = test_board[4][0] = test_board[5][0] = \
    test_board[6][0] = test_board[7][0] = 2;
    assert(checkVertical(test_board, 2, 0) == 1);
    test_board[1][0] = test_board[3][0] = test_board[4][0] = test_board[5][0] = \
    test_board[6][0] = test_board[7][0] = 0;
    cout<<"Case3: Passed!\n";

    test_board[0][0] = test_board[1][0] = test_board[3][0] = test_board[4][0] = test_board[5][0] = \
    test_board[6][0] = 2;
    assert(checkVertical(test_board, 2, 0) == 0);
    test_board[0][0] = test_board[1][0] = test_board[3][0] = test_board[4][0] = test_board[5][0] = \
    test_board[6][0] = 0;
    cout<<"Case4: Passed!\n";

    assert(checkVertical(test_board, 1, 1) == 0);
    cout<<"Case5: PASSED!\n";

    cout<<endl;
}

void Test_checkDiagonal_1() {
    cout<<"Test_checkDiagonal_1\n";
    test_board[0][0] = test_board[1][1] = test_board[2][2] = test_board[3][3] = test_board[4][4] = 1;
    assert(checkDiagonal_1(test_board, 1, 0, 0) == true);
    test_board[0][0] = test_board[1][1] = test_board[2][2] = test_board[3][3] = test_board[4][4] = 0;
    cout<<"Case1: Passed!\n";

    test_board[0][0] = test_board[1][1] = test_board[3][3] = test_board[4][4] = test_board[5][5] = \
    test_board[6][6] = test_board[7][7] = 1;
    assert(checkDiagonal_1(test_board, 1, 0, 0) == true);
    test_board[0][0] = test_board[1][1] = test_board[3][3] = test_board[4][4] = test_board[5][5] = \
    test_board[6][6] = test_board[7][7] = 0;
    cout<<"Case2: Passed!\n";

    cout<<endl;
}

void Test_DiagonalPatternsBackSlash() {
    cout<<"Test_DiagonalPatternsBackSlash\n";
    test_board[0][0] = test_board[1][1] = test_board[2][2] = test_board[3][3] = test_board[4][4] = 1;
    vector<pair<pair<int, int>, int>> r = DiagonalPatternsBackSlash(test_board, 1, 0, 0);
    assert(r.size() == 1);
    assert(r[0].first.first == 0);
    assert(r[0].first.second == 0);
    assert(r[0].second == 5);
    test_board[0][0] = test_board[1][1] = test_board[2][2] = test_board[3][3] = test_board[4][4] = 0;
    cout<<"Case1: Passed!\n";

    test_board[0][0] = test_board[1][1] = test_board[2][2] = test_board[4][4] = test_board[5][5] = 1;
    r = DiagonalPatternsBackSlash(test_board, 1, 0, 0);
    assert(r.size() == 2);
    assert(r[0].first.first == 0);
    assert(r[0].first.second == 0);
    assert(r[0].second == 3);
    assert(r[1].first.first == 4);
    assert(r[1].first.second == 4);
    assert(r[1].second == 2);
    test_board[0][0] = test_board[1][1] = test_board[2][2] = test_board[4][4] = test_board[5][5] = 0;
    cout<<"Case2: Passed!\n";

    test_board[10][10] = test_board[11][11] = test_board[12][12] = test_board[13][13] = test_board[14][14] = 1;
    r = DiagonalPatternsBackSlash(test_board, 1, 0, 0);
    assert(r.size() == 1);
    assert(r[0].first.first == 10);
    assert(r[0].first.second == 10);
    assert(r[0].second == 5);
    test_board[10][10] = test_board[11][11] = test_board[12][12] = test_board[13][13] = test_board[14][14] = 0;
    cout<<"Case3: Passed!\n";

    test_board[7][8] = test_board[8][9] = 1;
    r = DiagonalPatternsBackSlash(test_board, 1, 0, 1);
    assert(r.size() == 1);
    assert(r[0].first.first == 7);
    assert(r[0].first.second == 8);
    assert(r[0].second == 2);
    test_board[7][8] = test_board[8][9] = 0;
    cout<<"Case3: Passed!\n";

    cout<<endl;
}

void Test_DiagonalPatternsForwardSlash() {
    cout<<"Test_DiagonalPatternsForwardSlash\n";
    test_board[0][14] = test_board[1][13] = test_board[2][12] = test_board[3][11] = test_board[4][10] = 1;
    vector<pair<pair<int, int>, int>> r = DiagonalPatternsForwardSlash(test_board, 1, 0, 14);
    assert(r.size() == 1);
    assert(r[0].first.first == 0);
    assert(r[0].first.second == 14);
    assert(r[0].second == 5);
    test_board[0][14] = test_board[1][13] = test_board[2][12] = test_board[3][11] = test_board[4][10] = 0;
    cout<<"Case1: Passed!\n";

    test_board[0][14] = test_board[1][13] = test_board[2][12] = test_board[4][10] = test_board[5][9] = 1;
    r = DiagonalPatternsForwardSlash(test_board, 1, 0, 14);
    assert(r.size() == 2);
    assert(r[0].first.first == 0);
    assert(r[0].first.second == 14);
    assert(r[0].second == 3);
    assert(r[1].first.first == 4);
    assert(r[1].first.second == 10);
    assert(r[1].second == 2);
    test_board[0][14] = test_board[1][13] = test_board[2][12] = test_board[4][10] = test_board[5][9] = 0;
    cout<<"Case2: Passed!\n";

    test_board[7][7] = 1;
    r = DiagonalPatternsForwardSlash(test_board, 1, 0, 14);
    assert(r.size() == 1);
    assert(r[0].first.first == 7);
    assert(r[0].first.second == 7);
    assert(r[0].second == 1);
    test_board[7][7] = 0;
    cout<<"Case3: Passed!\n";

    // test_board[7][8] = test_board[8][9] = 1;
    // r = DiagonalPatternsBackSlash(test_board, 1, 0, 1);
    // assert(r.size() == 1);
    // assert(r[0].first.first == 7);
    // assert(r[0].first.second == 8);
    // assert(r[0].second == 2);
    // test_board[7][8] = test_board[8][9] = 0;
    // cout<<"Case3: Passed!\n";

    cout<<endl;
}

void Test_horizontalPatters() {
    cout<<"Test_horizontalPatters\n";
    test_board[0][0] = 1;
    vector<pair<int, int>> r = HorizontalPatterns(test_board, 1, 0);
    assert(r.size() == 1);
    assert(r[0].first == 0);
    assert(r[0].second == 0);
    test_board[0][0] = 0;
    cout<<"Case1: Passed!\n";

    test_board[0][0] = test_board[0][1] = 1;
    r = HorizontalPatterns(test_board, 1, 0);
    assert(r.size() == 1);
    assert(r[0].first == 0);
    assert(r[0].second == 1);
    cout<<"Case2: Passed!\n";

    test_board[0][13] = test_board[0][14] = 1;
    r = HorizontalPatterns(test_board, 1, 0);
    assert(r.size() == 2);
    assert(r[1].first == 13);
    assert(r[1].second == 14);
    cout<<"Case3: Passed!\n";

    test_board[0][12] = test_board[0][13] = 1;
    test_board[0][14] = 0;
    r = HorizontalPatterns(test_board, 1, 0);
    assert(r.size() == 2);
    assert(r[1].first == 12);
    assert(r[1].second == 13);
    cout<<"Case3: Passed!\n";

    test_board[0][0] = test_board[0][1] = test_board[0][12] = test_board[0][13] = test_board[0][14] = 0;
    cout<<endl;
}

void Test_verticalPatters() {
    cout<<"Test_verticalPatters\n";
    test_board[0][0] = 1;
    vector<pair<int, int>> r = VerticalPatterns(test_board, 1, 0);
    assert(r.size() == 1);
    assert(r[0].first == 0);
    assert(r[0].second == 0);
    test_board[0][0] = 0;
    cout<<"Case1: Passed!\n";

    test_board[0][0] = test_board[1][0] = 1;
    r = VerticalPatterns(test_board, 1, 0);
    assert(r.size() == 1);
    assert(r[0].first == 0);
    assert(r[0].second == 1);
    cout<<"Case2: Passed!\n";

    test_board[13][0] = test_board[14][0] = 1;
    r = VerticalPatterns(test_board, 1, 0);
    assert(r.size() == 2);
    assert(r[1].first == 13);
    assert(r[1].second == 14);
    cout<<"Case3: Passed!\n";

    test_board[12][0] = test_board[13][0] = 1;
    test_board[14][0] = 0;
    r = VerticalPatterns(test_board, 1, 0);
    assert(r.size() == 2);
    assert(r[1].first == 12);
    assert(r[1].second == 13);
    cout<<"Case3: Passed!\n";

    test_board[0][0] = test_board[1][0] = test_board[12][0] = test_board[13][0] = test_board[14][0] = 0;
    cout<<endl;
}

void Test_horizontalWeights() {
    cout<<"Test_horizontalWeights\n";

    int w1[15][15] = {0};
    test_board[0][0] = test_board[0][1] = 1;
    CalculateHorizontal(test_board, w1, 1);
    assert(w1[0][2] == 2);
    cout<<"Case1: Passed!\n";

    int w2[15][15] = {0};
    test_board[0][13] = test_board[0][14] = 1;
    test_board[0][12] = 2;
    CalculateHorizontal(test_board, w2, 1);
    assert(w2[0][2] == 2);
    assert(w2[0][12] == 0);
    cout<<"Case2: Passed!\n";

    
    int w3[15][15] = {0};
    test_board[0][12] = test_board[0][13] = 1;
    test_board[0][14] = 0;
    CalculateHorizontal(test_board, w3, 1);
    assert(w3[0][11] == 4);
    assert(w3[0][14] == 4);
    cout<<"Case3: Passed!\n";

    test_board[0][0] = test_board[0][1] = test_board[0][13] = test_board[0][14] = test_board[0][12] = 0;
    cout<<endl;
}

void Test_verticalWeights() {
    cout<<"Test_verticalWeights\n";

    int w1[15][15] = {0};
    test_board[0][0] = test_board[1][0] = 1;
    CalculateVertical(test_board, w1, 1);
    assert(w1[2][0] == 2);
    cout<<"Case1: Passed!\n";

    int w2[15][15] = {0};
    test_board[13][0] = test_board[14][0] = 1;
    test_board[12][0] = 2;
    CalculateVertical(test_board, w2, 1);
    assert(w2[2][0] == 2);
    assert(w2[12][0] == 0);
    cout<<"Case2: Passed!\n";

    
    int w3[15][15] = {0};
    test_board[12][0] = test_board[13][0] = 1;
    test_board[14][0] = 0;
    CalculateVertical(test_board, w3, 1);
    assert(w3[11][0] == 4);
    assert(w3[14][0] == 4);
    cout<<"Case3: Passed!\n";

    test_board[0][0] = test_board[1][0] = test_board[13][0] = test_board[14][0] = test_board[12][0] = 0;
    cout<<endl;
}

void Test_Weights() {
    cout<<"Test_Weights\n";

    int w1[15][15] = {0};
    test_board[7][7] = 1;
    CalculateWeights(test_board, w1, black);
    assert(w1[8][8] == 2);
    assert(w1[6][6] == 2);
    assert(w1[6][8] == 2);
    assert(w1[8][6] == 2);
    cout<<"Case1: Passed!\n";

    // int w2[15][15] = {0};
    // test_board[13][0] = test_board[14][0] = 1;
    // test_board[12][0] = 2;
    // CalculateVertical(test_board, w2, 1);
    // assert(w2[2][0] == 2);
    // assert(w2[12][0] == 0);
    // cout<<"Case2: Passed!\n";

    
    // int w3[15][15] = {0};
    // test_board[12][0] = test_board[13][0] = 1;
    // test_board[14][0] = 0;
    // CalculateVertical(test_board, w3, 1);
    // assert(w3[11][0] == 4);
    // assert(w3[14][0] == 4);
    // cout<<"Case3: Passed!\n";

    // test_board[0][0] = test_board[1][0] = test_board[13][0] = test_board[14][0] = test_board[12][0] = 0;
    cout<<endl;
}

int main() {
    cout<<"Tests:\n";
    Test_checkHorizontal();
    Test_checkVertical();
    Test_checkDiagonal_1();
    Test_horizontalPatters();
    Test_horizontalWeights();
    Test_verticalPatters();
    Test_verticalWeights();
    Test_DiagonalPatternsBackSlash();
    Test_DiagonalPatternsForwardSlash();
    Test_Weights();
    return 0;
}