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
	adjacentBombs = leftTop + leftCenter + leftBottom + top + bottom +
		rightTop + rightCenter + rightBottom;
	if (adjacentBombs > 0)
	{
		type = Cell::cellType::number;
	}
}

bool Cell::isRevealed()
{
	return revealed;
}

bool Cell::isNumber()
{
	return (type == Cell::cellType::number);
}

bool Cell::reveal()
{
	revealed = true;
	return (this->hasMine());
}

unsigned int Cell::getAdjacentBombs()
{
	if (type == Cell::cellType::number)
	{
		return adjacentBombs;
	}
	else
	{
		return 0;
	}
}
