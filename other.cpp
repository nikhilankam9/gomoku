#define ColorCode_Black			0
#define ColorCode_DarkBlue		1
#define ColorCode_DarkGreen		2
#define ColorCode_DarkCyan		3
#define ColorCode_DarkRed		4
#define ColorCode_DarkPink		5
#define ColorCode_DarkYellow	6
#define ColorCode_DarkWhite		7
#define ColorCode_Grey			8
#define ColorCode_Blue			9
#define ColorCode_Green			10
#define ColorCode_Cyan			11
#define ColorCode_Red			12
#define ColorCode_Pink			13
#define ColorCode_Yellow		14
#define ColorCode_White			15
#define default_ColorCode		7

#define VK_R 0x52

#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

void hideScrollbar(bool hide) {

	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);

	csbi.dwSize.X = csbi.dwMaximumWindowSize.X;
	csbi.dwSize.Y = csbi.dwMaximumWindowSize.Y;
	SetConsoleScreenBufferSize(hstdout, csbi.dwSize);

	HWND x = GetConsoleWindow();
	ShowScrollBar(x, SB_BOTH, !hide);
}

void resizeWindow(int height, int width) {

	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void clrscr() {
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;
	COORD	Home = { 0,0 };
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}

void hideCursor(bool hide) {

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 25;
	cci.bVisible = !hide;
	SetConsoleCursorInfo(hStdout, &cci);
}

void goto_yx(int line, int column) {
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void textcolor(int foregroundColor, int backgroundColor = ColorCode_Black) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), foregroundColor | backgroundColor);
}

class Map {

private:
	vector<vector<char>> body;

public:

	int height, width;
	int beginX, beginY;

	void init() {

		for (int i = 0; i < this->height; i++) {

			vector<char> row;
			//row.resize(this->width);
			for (int j = 0; j < this->width; j++) {

				row.push_back('_');
			}
			body.push_back(row);
		}
	}

	Map() {

	}

	Map(int h, int w, int begin_y, int begin_x) {

		this->height = h;
		this->width = w;
		this->beginX = begin_x;
		this->beginY = begin_y;

		init();
	}

	COORD getBeginPos() {

		COORD coord;
		coord.X = beginX;
		coord.Y = beginY;
		return coord;
	}

	void setBeginPos(int y, int x) {

		this->beginX = x;
		this->beginY = y;
	}

	void setSpot(int y, int x, char val) {

		body[y][x] = val;
	}

	char getSpot(int y, int x) {

		return this->body.at(y).at(x);
	}

	void printMap() {

		goto_yx(1, (width * 2 + beginX) / 2 - 5);
		textcolor(ColorCode_Green); cout << "GOMOKU";
		textcolor(ColorCode_Red); cout << " (CK)";

		textcolor(ColorCode_Yellow);
		goto_yx(beginY - 1, 0);
		for (int i = 0; i <= this->width * 2 + 2; i++) cout << "=";
		goto_yx(beginY + height, 0);
		for (int i = 0; i <= this->width * 2 + 2; i++) cout << "=";

		for (int i = 0; i < this->height; i++) {

			goto_yx(i + beginY, 0);
			cout << "|";
			goto_yx(i + beginY, width * 2 + 2);
			cout << "|";
		}

		for (int i = 0; i < this->height; i++) {

			goto_yx(beginY + i, beginX + 1);
			for (int j = 0; j < this->width; j++) {

				char spot = getSpot(i, j);
				if (spot == '_') textcolor(default_ColorCode);
				else if (spot == 'x') textcolor(ColorCode_Green);
				else if (spot == 'o') textcolor(ColorCode_Red);
				cout << spot << " ";
				textcolor(default_ColorCode);
			}
		}
	}

	bool checkRow(int y, int x, char spot, bool chan2dau) {

		int i = y;
		int j = x;
		int count = 0;
		while (i >= 0 && i < height && j >= 0 && j < width) {

			if (body[i][j] == spot) {
				count++;
			}
			else {
				if (count < 5) return false;
			}
			j++;
			if (count == 5) {

				if (chan2dau) {

					if (x - 1 >= 0) {

						if (spot == 'o') {
							if (body[y][x - 1] != 'x')
								return true;
						}
						else if (spot == 'x') {

							if (body[y][x - 1] != 'o')
								return true;
						}
					}
					else return true;

					if (j < width) {

						if (spot == 'o') {
							if (body[y][j] != 'x')
								return true;
						}
						else if (spot == 'x') {

							if (body[y][j] != 'o')
								return true;
						}
					}
					else return true;

					return false;
				}
				else {
					return true;
				}
			}
		}
		return false;
	}

	bool checkCol(int y, int x, char spot, bool chan2dau) {

		int i = y;
		int j = x;
		int count = 0;
		while (i >= 0 && i < height && j >= 0 && j < width) {

			if (body[i][j] == spot) {
				count++;
			}
			else {
				if (count < 5) return false;
			}
			i++;
			if (count == 5) {

				if (chan2dau) {

					if (y - 1 >= 0) {

						if (spot == 'o') {
							if (body[y-1][x] != 'x')
								return true;
						}
						else if (spot == 'x') {

							if (body[y-1][x] != 'o')
								return true;
						}
					}
					else return true;

					if (i < width) {

						if (spot == 'o') {
							if (body[i][x] != 'x')
								return true;
						}
						else if (spot == 'x') {

							if (body[i][x] != 'o')
								return true;
						}
					}
					else return true;

					return false;
				}
				else {
					return true;
				}
			}
		}
		return false;
	}

	bool checkMainDiagonal(int y, int x, char spot, bool chan2dau) {

		int i = y;
		int j = x;
		int count = 0;
		while (i >= 0 && i < height && j >= 0 && j < width) {

			if (body[i][j] == spot) {
				count++;
			}
			else {
				if (count < 5) return false;
			}
			j++;
			i++;
			if (count == 5) {

				if (chan2dau) {

					if (x - 1 >= 0 && y - 1 >= 0) {

						if (spot == 'o') {
							if (body[y - 1][x - 1] != 'x')
								return true;
						}
						else if (spot == 'x') {

							if (body[y - 1][x - 1] != 'o')
								return true;
						}
					}
					else return true;

					if (j < width && i < height) {

						if (spot == 'o') {
							if (body[i][j] != 'x')
								return true;
						}
						else if (spot == 'x') {

							if (body[i][j] != 'o')
								return true;
						}
					}
					else return true;

					return false;
				}
				else {
					return true;
				}
			}
		}
		return false;
	}
	bool checkSemiDiagonal(int y, int x, char spot, bool chan2dau) {

		int count = 0;
		int i = y;
		int j = x;
		while (i >= 0 && i < height && j >= 0 && j < width) {

			if (body[i][j] == spot) {
				count++;
			}
			else {
				if (count < 5) return false;
			}
			j++;
			i--;
			if (count == 5) {

				if (chan2dau) {

					if (x - 1 >= 0 && y + 1 < height) {

						if (spot == 'o') {
							if (body[y + 1][x - 1] != 'x')
								return true;
						}
						else if (spot == 'x') {

							if (body[y + 1][x - 1] != 'o')
								return true;
						}
					}
					else return true;

					if (j < width && i >= 0) {

						if (spot == 'o') {
							if (body[i][j] != 'x')
								return true;
						}
						else if (spot == 'x') {

							if (body[i][j] != 'o')
								return true;
						}
					}
					else return true;

					return false;
				}
				else {
					return true;
				}
			}
		}
		return false;
	}
	bool isMapFull() {

		for (int i = 0; i < this->height; i++) {

			for (int j = 0; j < this->width; j++) {

				if (body[i][j] == '_') return false;
			}
		}
		return true;
	}
};

enum Mode { PVP, PVE };
enum Flag { None, Turn, Undo , Pause, Exit, Restart};

struct InputResult {

	int inputCode;
	COORD clickCoord;
};

class InputChecker {

private:
	HANDLE hStdin;
	DWORD fdwSaveOldMode;
	DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf;

public:

	InputChecker() {

		hStdin = GetStdHandle(STD_INPUT_HANDLE);
		GetConsoleMode(hStdin, &fdwSaveOldMode);
		fdwMode = ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS;
		SetConsoleMode(hStdin, fdwMode);
	}

	InputResult getInput() {

		while (true) {

			InputResult ipRes;
			ReadConsoleInput(hStdin, &irInBuf, 1, &cNumRead);
			switch (irInBuf.EventType) {
			case KEY_EVENT:

				if (irInBuf.Event.KeyEvent.wVirtualKeyCode == VK_SPACE
					|| irInBuf.Event.KeyEvent.wVirtualKeyCode == VK_RETURN
					|| irInBuf.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE
					|| irInBuf.Event.KeyEvent.wVirtualKeyCode == VK_BACK
					|| irInBuf.Event.KeyEvent.wVirtualKeyCode == VK_R) {

					Sleep(100);
					ipRes.inputCode = irInBuf.Event.KeyEvent.wVirtualKeyCode;
					FlushConsoleInputBuffer(hStdin);
					return ipRes;
				}
				break;
			case MOUSE_EVENT:

				COORD coord;
				if (irInBuf.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
					coord.X = irInBuf.Event.MouseEvent.dwMousePosition.X;
					coord.Y = irInBuf.Event.MouseEvent.dwMousePosition.Y;
					ipRes.inputCode = VK_LBUTTON;
					ipRes.clickCoord = coord;
					FlushConsoleInputBuffer(hStdin);
					return ipRes;
				}
				break;
			}
			FlushConsoleInputBuffer(hStdin);
			Sleep(10);
		}
	}
};

class Computer {

private:
	bool chan2dau;
	char my_spot, enemy_spot;
	const long defensePoint[7] = { 0, 1, 9, 81, 729, 6561, 59049 };
	const long attackPoint[7] = { 0, 3, 24, 192, 1536, 12288, 98304 };

	Map currMap = Map(20, 30, 3, 1);

	COORD findBestMove() {

		COORD bestMove;
		bestMove.Y = 1;
		bestMove.X = 1;
		long moveMaxVal = 0;

		for (int i = 0; i < currMap.height; i++) {

			for (int j = 0; j < currMap.width; j++) {

				if (currMap.getSpot(i, j) == '_') {

					long attackVal
						= getVerticalAttackVal(i, j)
						+ getHorizontalAttackVal(i, j)
						+ getMainDiagonalAttackVal(i, j)
						+ getSemiDiagonalAttackVal(i, j);

					long defenseVal
						= getVerticalDefenseVal(i, j)
						+ getHorizontalDefenseVal(i, j)
						+ getMainDiagonalDefenseVal(i, j)
						+ getSemiDiagonalDefenseVal(i, j);

					long tempVal = max(attackVal, defenseVal);
					if (moveMaxVal < tempVal) {

						moveMaxVal = tempVal;
						bestMove.Y = i;
						bestMove.X = j;
					}
				}
			}
		}

		return bestMove;
	}

#pragma region attack

	long getVerticalAttackVal(int curRow, int curCol) {

		long totalVal = 0;
		int allies = 0;
		int enemies = 0;

		for (int i = 1; i < 6 && curRow + i < currMap.height; i++) {

			if (currMap.getSpot(curRow + i, curCol) == my_spot) {

				allies++;
			}
			else if (currMap.getSpot(curRow + i, curCol) == enemy_spot) {

				enemies++;
				break;
			}
			else {

				break;
			}
		}

		for (int i = 1; i < 6 && curRow - i >= 0; i++) {

			if (currMap.getSpot(curRow - i, curCol) == my_spot) {

				allies++;
			}
			else if (currMap.getSpot(curRow - i, curCol) == enemy_spot) {

				enemies++;
				break;
			}
			else {

				break;
			}
		}

		if (chan2dau && enemies == 2)
			return 0;

		totalVal -= defensePoint[enemies];
		totalVal += attackPoint[allies];

		return totalVal;
	}
	long getHorizontalAttackVal(int curRow, int curCol) {

		long totalVal = 0;
		int allies = 0;
		int enemies = 0;

		for (int i = 1; i < 6 && curCol + i < currMap.width; i++) {

			if (currMap.getSpot(curRow, curCol + i) == my_spot) {

				allies++;
			}
			else if (currMap.getSpot(curRow, curCol + i) == enemy_spot) {

				enemies++;
				break;
			}
			else {

				break;
			}
		}

		for (int i = 1; i < 6 && curCol - i >= 0; i++) {

			if (currMap.getSpot(curRow, curCol - i) == my_spot) {

				allies++;
			}
			else if (currMap.getSpot(curRow, curCol - i) == enemy_spot) {

				enemies++;
				break;
			}
			else {

				break;
			}
		}

		if (chan2dau && enemies == 2)
			return 0;

		totalVal -= defensePoint[enemies + 1];
		totalVal += attackPoint[allies];

		return totalVal;
	}
	long getMainDiagonalAttackVal(int curRow, int curCol) {

		long totalVal = 0;
		int allies = 0;
		int enemies = 0;

		for (int i = 1; i < 6 && curRow + i < currMap.height && curCol + i < currMap.width; i++) {

			if (currMap.getSpot(curRow + i, curCol + i) == my_spot) {

				allies++;
			}
			else if (currMap.getSpot(curRow + i, curCol + i) == enemy_spot) {

				enemies++;
				break;
			}
			else {

				break;
			}
		}

		for (int i = 1; i < 6 && curRow - i >= 0 && curCol - i >= 0; i++) {

			if (currMap.getSpot(curRow - i, curCol - i) == my_spot) {

				allies++;
			}
			else if (currMap.getSpot(curRow - i, curCol - i) == enemy_spot) {

				enemies++;
				break;
			}
			else {

				break;
			}
		}

		if (chan2dau && enemies == 2)
			return 0;

		totalVal -= defensePoint[enemies + 1];
		totalVal += attackPoint[allies];

		return totalVal;
	}
	long getSemiDiagonalAttackVal(int curRow, int curCol) {

		long totalVal = 0;
		int allies = 0;
		int enemies = 0;

		for (int i = 1; i < 6 && curRow - i >= 0 && curCol + i < currMap.width; i++) {

			if (currMap.getSpot(curRow - i, curCol + i) == my_spot) {

				allies++;
			}
			else if (currMap.getSpot(curRow - i, curCol + i) == enemy_spot) {

				enemies++;
				break;
			}
			else {

				break;
			}
		}

		for (int i = 1; i < 6 && curRow + i < currMap.height && curCol - i >= 0; i++) {

			if (currMap.getSpot(curRow + i, curCol - i) == my_spot) {

				allies++;
			}
			else if (currMap.getSpot(curRow + i, curCol - i) == enemy_spot) {

				enemies++;
				break;
			}
			else {

				break;
			}
		}

		if (chan2dau && enemies == 2)
			return 0;

		totalVal -= defensePoint[enemies + 1];
		totalVal += attackPoint[allies];

		return totalVal;
	}

#pragma endregion

#pragma region defense

	long getVerticalDefenseVal(int curRow, int curCol) {

		long totalVal = 0;
		int allies = 0;
		int enemies = 0;

		for (int i = 1; i < 6 && curRow + i < currMap.height; i++) {

			if (currMap.getSpot(curRow + i, curCol) == my_spot) {

				allies++;
				break;
			}
			else if (currMap.getSpot(curRow + i, curCol) == enemy_spot) {

				enemies++;
			}
			else {

				break;
			}
		}

		for (int i = 1; i < 6 && curRow - i >= 0; i++) {

			if (currMap.getSpot(curRow - i, curCol) == my_spot) {

				allies++;
				break;
			}
			else if (currMap.getSpot(curRow - i, curCol) == enemy_spot) {

				enemies++;
			}
			else {

				break;
			}
		}

		if (chan2dau && allies == 2)
			return 0;

		totalVal += defensePoint[enemies];
		//totalVal += attackPoint[allies];

		return totalVal;
	}
	long getHorizontalDefenseVal(int curRow, int curCol) {

		long totalVal = 0;
		int allies = 0;
		int enemies = 0;

		for (int i = 1; i < 6 && curCol + i < currMap.width; i++) {

			if (currMap.getSpot(curRow, curCol + i) == my_spot) {

				allies++;
				break;
			}
			else if (currMap.getSpot(curRow, curCol + i) == enemy_spot) {

				enemies++;
			}
			else {

				break;
			}
		}

		for (int i = 1; i < 6 && curCol - i >= 0; i++) {

			if (currMap.getSpot(curRow, curCol - i) == my_spot) {

				allies++;
				break;
			}
			else if (currMap.getSpot(curRow, curCol - i) == enemy_spot) {

				enemies++;
			}
			else {

				break;
			}
		}

		if (chan2dau && allies == 2)
			return 0;

		totalVal += defensePoint[enemies];

		return totalVal;
	}
	long getMainDiagonalDefenseVal(int curRow, int curCol) {

		long totalVal = 0;
		int allies = 0;
		int enemies = 0;

		for (int i = 1; i < 6 && curRow + i < currMap.height && curCol + i < currMap.width; i++) {

			if (currMap.getSpot(curRow + i, curCol + i) == my_spot) {

				allies++;
				break;
			}
			else if (currMap.getSpot(curRow + i, curCol + i) == enemy_spot) {

				enemies++;
			}
			else {

				break;
			}
		}

		for (int i = 1; i < 6 && curRow - i >= 0 && curCol - i >= 0; i++) {

			if (currMap.getSpot(curRow - i, curCol - i) == my_spot) {

				allies++;
				break;
			}
			else if (currMap.getSpot(curRow - i, curCol - i) == enemy_spot) {

				enemies++;
			}
			else {

				break;
			}
		}

		if (chan2dau && allies == 2)
			return 0;

		totalVal += defensePoint[enemies];

		return totalVal;
	}
	long getSemiDiagonalDefenseVal(int curRow, int curCol) {

		long totalVal = 0;
		int allies = 0;
		int enemies = 0;

		for (int i = 1; i < 6 && curRow - i >= 0 && curCol + i < currMap.width; i++) {

			if (currMap.getSpot(curRow - i, curCol + i) == my_spot) {

				allies++;
				break;
			}
			else if (currMap.getSpot(curRow - i, curCol + i) == enemy_spot) {

				enemies++;
			}
			else {

				break;
			}
		}

		for (int i = 1; i < 6 && curRow + i < currMap.height && curCol - i >= 0; i++) {

			if (currMap.getSpot(curRow + i, curCol - i) == my_spot) {

				allies++;
				break;
			}
			else if (currMap.getSpot(curRow + i, curCol - i) == enemy_spot) {

				enemies++;
			}
			else {

				break;
			}
		}

		if (chan2dau && allies == 2)
			return 0;

		totalVal += defensePoint[enemies];

		return totalVal;
	}

#pragma endregion

public:
	Computer(bool chan2dau, char my_spot, char enemy_spot) {

		this->chan2dau = chan2dau;
		this->my_spot = my_spot;
		this->enemy_spot = enemy_spot;
	}

	void Turn(Map *currentMap) {

		currMap = *currentMap;
		COORD spot = findBestMove();
		currentMap->setSpot(spot.Y, spot.X, my_spot);
	}
};

class GameManager {

private:

	int winner = 0;
	int turnCount = 0;
	int onTurnPlayer = 1;
	bool chan2dau = false;

	Mode playMode = PVP;
	vector<Map> historyMap;
	Map currentMap;
	InputChecker inputChecker;
	Flag currentFlag = None;
	Computer *computer;

	Flag HumanTurn() {

		InputResult playerInput = inputChecker.getInput();
		if (playerInput.inputCode == VK_LBUTTON) {

			if (playerInput.clickCoord.X%2 == 0 && playerInput.clickCoord.X >= currentMap.getBeginPos().X + 1 && playerInput.clickCoord.X < currentMap.getBeginPos().X + 1 + currentMap.width * 2
				&& playerInput.clickCoord.Y >= currentMap.getBeginPos().Y && playerInput.clickCoord.Y < currentMap.getBeginPos().Y + currentMap.height) {

				COORD turnPos;
				turnPos.Y = playerInput.clickCoord.Y - currentMap.getBeginPos().Y;
				turnPos.X = playerInput.clickCoord.X/2 - currentMap.getBeginPos().X;
				if (currentMap.getSpot(turnPos.Y, turnPos.X) == '_') {

					historyMap.push_back(currentMap);
					if (onTurnPlayer == 1) {
						currentMap.setSpot(turnPos.Y, turnPos.X, 'x');
					}
					else {
						currentMap.setSpot(turnPos.Y, turnPos.X, 'o');
					}
					return Turn;
				}
				else {

					return None;
				}
			}
			else {

				return None;
			}
		}
		else if (playerInput.inputCode == VK_SPACE) {

			return Pause;
		}
		else if (playerInput.inputCode == VK_ESCAPE) {

			return Exit;
		}
		else if (playerInput.inputCode == VK_BACK) {

			return Undo;
		}
		else if (playerInput.inputCode == VK_R) {

			return Restart;
		}
		else {

			return None;
		}
		return None;
	}

	int checkWin() {

		int onCheckPlayer = 0;
		for (int i = 0; i < currentMap.height; i++) {

			for (int j = 0; j < currentMap.width; j++) {

				if (currentMap.getSpot(i, j) != '_') {

					if (currentMap.getSpot(i, j) == 'x') {
						onCheckPlayer = 1;
					}
					else {
						onCheckPlayer = 2;
					}
					if (currentMap.checkRow(i, j, currentMap.getSpot(i, j), chan2dau)
						|| currentMap.checkCol(i, j, currentMap.getSpot(i, j), chan2dau)
						|| currentMap.checkMainDiagonal(i, j, currentMap.getSpot(i, j), chan2dau)
						|| currentMap.checkSemiDiagonal(i, j, currentMap.getSpot(i, j), chan2dau))
						return onCheckPlayer;
				}
			}
		}
		return 0;
	}

public:

	int GameManger() {

	}

	void init(Mode mode, bool chan2dau, int mapHeight, int mapWidth) {

		this->playMode = mode;
		this->chan2dau = chan2dau;

		computer = new Computer(chan2dau, 'o', 'x');

		winner = 0;
		onTurnPlayer = 1;
		turnCount = 0;
		currentMap = Map(mapHeight, mapWidth, 3, 1);
		currentFlag = None;
		historyMap.clear();
	}

	void printUI() {

		textcolor(ColorCode_Pink);
		goto_yx(currentMap.beginY - 1, currentMap.beginX + currentMap.width * 2 + 4);
		cout << "Field-size: " << currentMap.height << "x" << currentMap.width;

		textcolor(ColorCode_White);
		goto_yx(currentMap.beginY, currentMap.beginX + currentMap.width * 2 + 4);
		cout << "Current turn: ";
		if (onTurnPlayer == 1) textcolor(ColorCode_Green); else textcolor(ColorCode_Red);
		cout << "Player " << onTurnPlayer;

		textcolor(ColorCode_Cyan);
		goto_yx(currentMap.beginY + 2, currentMap.beginX + currentMap.width * 2 + 4);
		cout << "Press R to restart game";
		goto_yx(currentMap.beginY + 3, currentMap.beginX + currentMap.width * 2 + 4);
		cout << "Press Backspace to undo";
		goto_yx(currentMap.beginY + 4, currentMap.beginX + currentMap.width * 2 + 4);
		cout << "Press ESC to quit game ";
	}

	void DoUndo() {

		if (historyMap.size() > 0) {
			currentMap = historyMap.back();
			historyMap.pop_back();
			turnCount--;
		}
	}

	void Play(Mode mode, bool chan2dau, int mapHeight, int mapWidth) {
	begin:
		resizeWindow(mapHeight * 20 + 60, mapWidth*16 + 250);
		hideCursor(true);
		clrscr();
		init(mode, chan2dau, mapHeight, mapWidth);
		while (true) {

			currentMap.printMap();
			onTurnPlayer = turnCount % 2 + 1;
			printUI();

			if (mode == PVP || (mode == PVE && onTurnPlayer == 1)) {
				currentFlag = HumanTurn();
				if (currentFlag == Turn) turnCount++;
				else {
					handle_flag:
					if (currentFlag == Exit) goto out;
					else if (currentFlag == Undo) {

						textcolor(ColorCode_White);
						goto_yx(24, 0); cout << "Undo";
						Sleep(300);
						DoUndo();
						if (mode == PVE) DoUndo();
						goto_yx(24, 0); cout << "      ";
					}
					else if (currentFlag == Restart) goto begin;
				}
			}
			else if (mode == PVE && onTurnPlayer == 2) {
				historyMap.push_back(currentMap);
				computer->Turn(&currentMap);
				turnCount++;
			}

			winner = checkWin();
			if (winner != 0 || currentMap.isMapFull()) {
				Sleep(100);
				break;
			}
		}
		currentMap.printMap();
		if (winner == 1) textcolor(ColorCode_Green);
		else if (winner == 2) textcolor(ColorCode_Red);
		else if (winner == 0) textcolor(ColorCode_Cyan);
		goto_yx(currentMap.height + currentMap.getBeginPos().Y + 1, (currentMap.width + currentMap.getBeginPos().X) - 6);

		if (winner != 0) cout << "Player " << winner << " won!";
		else cout << "Draw game!";

		while (true) {

			if (GetAsyncKeyState(VK_RETURN) || GetAsyncKeyState(0x52)) {
				clrscr();
				goto begin;
			}
			else if (GetAsyncKeyState(VK_ESCAPE))
				goto out;
			else if (GetAsyncKeyState(VK_BACK)) {

				clrscr();
				currentFlag = Undo;
				winner = 0;
				Sleep(100);
				goto handle_flag;
			}
		}
	out: { Sleep(200); clrscr(); }
	}
};

class GameLoader {

private:
	int mapWidth, mapHeight, screenWidth, screenHeight;
	GameManager *gameManager;
	vector<string> choiceMenu;

public:
	GameLoader() {

		this->mapHeight = 20;
		this->mapWidth = 30;
		this->screenHeight = this->mapHeight + 2 + 2;
		this->screenWidth = this->mapWidth*2 + 2;

		resizeWindow(screenHeight * 20, screenWidth * 8);
		hideScrollbar(true);
	}

	void showBanner() {

		goto_yx(1, screenWidth / 2 - 6);
		textcolor(ColorCode_Green); cout << "GOMOKU";
		textcolor(ColorCode_Red); cout << " (CK)";
	}

	void Load() {

		hideCursor(true);

		showBanner();

		choiceMenu.clear();
		choiceMenu.push_back("Play PVP mode");
		choiceMenu.push_back("Play PVE mode");
		choiceMenu.push_back("Set field-size");
		choiceMenu.push_back("Quit game");

		int choicedMode = 0;
		while (true) {

			showBanner();

			if (choicedMode < 0) choicedMode = choiceMenu.size() - 1;
			if (choicedMode >= choiceMenu.size()) choicedMode = 0;

			for (int i = 0; i < choiceMenu.size(); i++) {

				goto_yx(3 + i*2, screenWidth / 2 - choiceMenu[i].length()/2);
				if (i == choicedMode) textcolor(ColorCode_Yellow, BACKGROUND_RED);
				else textcolor(ColorCode_Green);
				cout << choiceMenu[i];
			}

			Sleep(65);
			if (GetAsyncKeyState(VK_UP) & 0x8000) choicedMode--;
			else if (GetAsyncKeyState(VK_DOWN) & 0x8000) choicedMode++;
			else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) break;
			else if (GetAsyncKeyState(VK_RETURN) & 0x8000) {

				Sleep(100);
				if (choicedMode == 3) {

					break;
				}
				else if (choicedMode == 2) {

					loadSetSizeMenu();
				}
				else {

					Mode mode;
					if (choicedMode == 0) mode = PVP;
					else mode = PVE;
					bool chan2dau = askForChan2dau();
					system("color 07");

					gameManager = new GameManager();
					gameManager->Play(mode, chan2dau, mapHeight, mapWidth);
					resizeWindow(screenHeight * 20, screenWidth * 8);
					hideCursor(true);
				}
			}
		}
	}

	bool askForChan2dau() {

		textcolor(ColorCode_Yellow);
		goto_yx(3 + choiceMenu.size() * 2, screenWidth / 2 - 8);
		cout << "Is the selection done ? (y/n)";

		while (true) {

			if (GetAsyncKeyState(0x4E) & 0x8000) {

				return false;
			}
			else if (GetAsyncKeyState(0x59) & 0x8000) {

				return true;
			}
		}
	}

	void loadSetSizeMenu() {

		Sleep(100);
		int h, w;
		clrscr();
		system("color 07");
		showBanner();
		hideCursor(false);
		textcolor(ColorCode_Yellow);
		goto_yx(3, screenWidth / 2 - 7); cout << "Enter height: "; cin >> h;
		goto_yx(5, screenWidth / 2 - 7); cout << "Enter width: "; cin >> w;
		this->mapHeight = h;
		this->mapWidth = w;
		hideCursor(true);
		clrscr();
		Sleep(100);
	}
};

int main() {

	GameLoader gameLoader;
	gameLoader.Load();
	return 0;
}
