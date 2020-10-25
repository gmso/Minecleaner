#include "Cell.h"

Cell::Cell()
{
	type = Cell::cellType::empty;
	revealed = false;
	adjacentBombs = 0;
}

Cell::~Cell()
{
}

bool Cell::hasMine()
{
	return (type == Cell::cellType::mine);
}

void Cell::addMine()
{
	type = Cell::cellType::mine;
}

void Cell::addNumber(unsigned int leftTop, unsigned int leftCenter, unsigned int leftBottom, unsigned int top, unsigned int bottom, unsigned int rightTop, unsigned int rightCenter, unsigned int rightBottom)
{
	type = Cell::cellType::number;
	adjacentBombs = leftTop + leftCenter + leftBottom + top + bottom +
		rightTop + rightCenter + rightBottom;
}

bool Cell::isRevealed()
{
	return revealed;
}

bool Cell::reveal()
{
	revealed = true;
	return (this->hasMine());
}
