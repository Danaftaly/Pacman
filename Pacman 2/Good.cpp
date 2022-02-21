#include "Good.h"

void Good::botMove(const Board& board, Bot& bot, const Position pacPos)
{
	if (typeid(*strategy) == typeid(Best))
	{
		if (paceCounter > 20)
		{
			setStrategy(new Novice(randRatio));
			paceCounter = 0;
		}
	}
	else
	{
		if (paceCounter > 5)
		{
			setStrategy(new Best);
			paceCounter = 0;
		}
	}

	strategy->botMove(board, bot, pacPos);
	paceCounter++;
}