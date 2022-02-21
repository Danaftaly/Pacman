#include "Novice.h"

void Novice::botMove(const Board& board, Bot& bot, const Position pacPos)
{
	Position tempPos(bot.getPos());
	char tempDirection;

	do {
		if (bot.getPaceCounter() == 0 || !(tempPos == bot.getPos()))
			tempDirection = dirEncode[(rand() % 4)];
		else
			tempDirection = bot.getDirection();

		tempPos = bot.getPos();
		bot.generateNewPos(tempPos, tempDirection, board);

	} while (tempPos.isInvalid() || board.isBlocked(tempPos));

	bot.setDirection(tempDirection);
	bot.move(tempPos, board.getChar(bot.getPos()));

	if (bot.getPaceCounter() == randRatio)
		bot.setPaceCounter(0);
	else
		bot.setPaceCounter(bot.getPaceCounter() + 1);
}