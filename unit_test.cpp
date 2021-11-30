#include <iostream>
#include <assert.h>
#include "board.h"

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
}

int main() {
    cout<<"Tests:\n";
    Test_checkHorizontal();
    Test_checkVertical();
    Test_checkDiagonal_1();
    return 0;
}