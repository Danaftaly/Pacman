#ifndef CREATURE_H
#define CREATURE_H

#include "Utils.h"
#include "Board.h"
#include "Position.h"
#include "Mode.h"

class Creature {
    char direction = DEFAULT;
    Position initPos;
    Position pos;
    char sign;
    Color color;
    bool colorFlag; 
    int paceCounter;

protected:
    enum { Left = 'a', Up = 'w', Right = 'd', Down = 'x', Stay = 's', DEFAULT = 0 };
    enum { WALL = '#', BLANK = ' ', FOOD = '.', Pac_Sign = '@' };
    char dirEncode[4] = { Left, Up, Right, Down };
    Mode* mode;

public:
    Creature(char _Sign, Color _color, bool _colorFlag): sign(_Sign), color(_color), colorFlag(_colorFlag){}
    Creature(char _Sign, Color _color, bool _colorFlag, Position _initPos)
            : sign(_Sign), color(_color), colorFlag(_colorFlag), initPos(_initPos), pos(_initPos) {}

    void draw();
    void setToStartPos();
    void move(const Position newPos, const char ch);
    void generateNewPos(Position& temp, char direction, const Board& board);

    char getSign() { return sign; }
    void setSign(char _sign) { sign = _sign; }
    int getPaceCounter()const { return paceCounter; }
    void setPaceCounter(const int _paceCounter) { paceCounter = _paceCounter; }
    Position getPos()const { return pos; }
    void setInitPos(const Position& _initPos) { pos = initPos = _initPos; }
    char getDirection()const { return direction; }
    void setDirection(const char _dir) { direction = _dir; }
    void setDiretcion(const Position& newPos);
    Mode* getMode() { return mode; }
    void setMode(Mode* _mode) { mode = _mode; }
    
};

#endif
