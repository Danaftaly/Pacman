#ifndef BOARD_H
#define BOARD_H

#include "Utils.h"
#include "Position.h"
#include "Mode.h"

class Board {
	enum { MAX_WIDTH = 80, MAX_HEIGHT = 25, LEGEND_WIDTH = 20, LEGEND_HEIGHT = 3, MAX_GHOST_NUM = 4 };
	enum GameSign{ GameSign_FOOD = '.', GameSign_BLANK = ' ', GameSign_LEGEND = 'L', GameSign_WALL = '#'};
	enum PrintSign{ PrintSign_WALL = 177, PrintSign_BLANK = ' ', PrintSign_PAC_LED = 219, PrintSign_FOOD = 250 };
	enum FileSign{ FileSign_WALL = '#', FileSign_FOOD = ' ',  FileSign_BLANK = '%', FileSign_LEGEND = '&'};
	enum { PAC = '@', GHOST = '$' };

	vector<string> board;
	bool colorFlag;
	Mode* mode;

	void fit1stLineForLegend();
	bool isInRange(const int x, const int a, const int b)const { return (a <= x && x < b); }
public:
	Board(bool _colorFlag) : colorFlag(_colorFlag) {}

	void loadBoardFromFile(string fileName);
	int Init(vector<Position>& startPositions, Mode* mode);
	void print();
	void removeFood(const int x, const int y) { board[y][x] = ' '; }
	void removeFood(const Position pos) { removeFood(pos.get_x(), pos.get_y()); }
	bool isValidPos(const int x, const int y)const { return (0 <= x && x < board[0].size() && 0 <= y && y < board.size()); }
	bool isValidPos(const Position pos)const { return isValidPos(pos.get_x(), pos.get_y()); }
	bool isBlocked(const int x, const int y)const { return (getChar(x, y) == GameSign_WALL || isalpha(getChar(x, y))); }
	bool isBlocked(const Position pos)const { return isBlocked(pos.get_x(), pos.get_y()); }

	int getWidth()const { return static_cast<int>(board[0].size()); }
	int getHeight()const { return static_cast<int>(board.size()); }
	int getQurter(const int x, const int y)const;
	int getQurter(const Position pos)const { return getQurter(pos.get_x(), pos.get_y()); }
	char getChar(int x, int y)const { return board[y][x]; }
	char getChar(Position pos)const { return board[pos.get_y()][pos.get_x()]; }
};

#endif


