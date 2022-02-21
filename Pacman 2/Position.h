#ifndef POSITION_H
#define POSITION_H

#include "Utils.h"

class Position {
	enum { Left = 'a', Up = 'w', Right = 'd', Down = 'x' };
	enum { GameSign_FOOD = '.', PrintSign_FOOD = 250, FileSign_BLANK = '%', PrintSign_BLANK = ' ', WIDTH = 80};

	int x;
	int y;
public:
	Position() {}
	Position(int _x, int _y) : x(_x), y(_y) {}
	Position(const Position& other) { *this = other; }

	void printToScreen(char ch);
	bool isInvalid() { return (x == -1 || y == -1); }

	void set(int _x, int _y) { x = _x; y = _y; }
	int get_x()const { return x; }
	int get_y()const { return y; }

	bool operator==(const Position& p)const { return(this->x == p.get_x() && this->y == p.get_y()); }
};

#endif