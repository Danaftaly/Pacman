#ifndef BEST_H
#define BEST_H

#include "Strategy.h"

#include "math.h"
#include <array>
#include <set>
#include <tuple>

using std::array;
typedef std::pair<int, int> Pair;
typedef std::tuple<int, int, int> Tuple;

struct cell {
    Pair parent;
    int f, g, h;

    cell() : parent(-1, -1), f(-1), g(-1), h(-1) {}
};

class Best : public Strategy {
	int pacQurter;
	stack<Position> pathToPac;

    stack<Position> aStarAlgorithm(const Board& board, const Position pos, const Position pacPos);
    stack<Position> tracePath(const vector<vector<cell>>& cellDetails, const Position pacPos);
    int calculateHValue(const Pair& src, const Position pacPos)const { return (abs(src.first - pacPos.get_y()) + abs(src.second - pacPos.get_x())); }
public:
    Best() : pacQurter(0){}

	void botMove(const Board& board, Bot& bot, const Position pacPos) override;
	void initPacQurter() override { pacQurter = 0; }
    bool isPathToPacExist(const Board& board, Bot& bot, const Position pacPos) override;
};

#endif
