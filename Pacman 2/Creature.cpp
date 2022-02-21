#include "Creature.h"

void Creature::draw()
{
	if (mode->isSilent())
		return;

	gotoxy(this->pos.get_x(), this->pos.get_y());
	if (this->colorFlag) setTextColor(this->color);
	cout << (char)sign;
	if (this->colorFlag) setTextColor(Color::WHITE);
}

void Creature::setToStartPos()
{
	this->pos = this->initPos;
	this->direction = DEFAULT;
	this->setPaceCounter(0);
	this->draw();
}

void Creature::move(const Position newPos, const char ch)
{
	if (!mode->isSilent()) 
		this->pos.printToScreen(ch);

	this->pos = newPos;
	this->draw();
}

void Creature::generateNewPos(Position& temp, char direction, const Board& board)
{
	int x = this->getPos().get_x();
	int y = this->getPos().get_y();

	switch (direction)
	{
	case Left:
		if (x == 0) // left tunnel 
		{
			if (sign == Pac_Sign)
				temp.set(board.getWidth() - 1, y);
			else
				temp.set(-1, -1);
		}
		else
			temp.set(x - 1, y);
		break;
	case Up:
		if (y == 0) // upper tunnel 
		{
			if (sign == Pac_Sign)
				temp.set(x, board.getHeight() - 1);
			else
				temp.set(-1, -1);
		}
		else
			temp.set(x, y - 1);
		break;
	case Right:
		if (x == board.getWidth() - 1) // right tunnel 
		{
			if (sign == Pac_Sign)
				temp.set(0, y);
			else
				temp.set(-1, -1);
		}
		else
			temp.set(x + 1, y);
		break;
	case Down:
		if (y == board.getHeight() - 1) // down tunnel 
		{
			if (sign == Pac_Sign)
				temp.set(x, 0);
			else
				temp.set(-1, -1);
		}
		else
			temp.set(x, y + 1);
		break;
	default:
		break;
	}
}

void Creature::setDiretcion(const Position& newPos)
{
	if (this->getPos().get_x() == newPos.get_x() + 1) // left
		this->direction = Left;

	if (this->getPos().get_y() == newPos.get_y() + 1) // up
		this->direction = Up;

	if (this->getPos().get_x() + 1 == newPos.get_x()) // right
		this->direction = Right;

	if (this->getPos().get_y() + 1 == newPos.get_y()) // down
		this->direction = Down;
}
