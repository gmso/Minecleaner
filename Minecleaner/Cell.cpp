#include "Cell.h"

Cell::Cell()
{
	type = Cell::cellType::empty;
	mark = markType::none;
	revealed = false;
	hovered = false;
	adjacentBombs = 0;
	totalNeighbors = 0;
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

bool Cell::isEmpty()
{
	return (type == Cell::cellType::empty);
}

bool Cell::reveal(unsigned int livesRemaining)
{
	if (livesRemaining > 0 && 
		(this->hasMine()))
	{
		mark = markType::saved;
	}
	else
	{
		revealed = true;
	}
	return (this->hasMine());
}

void Cell::hide()
{
	revealed = true;
}

void Cell::hover()
{
	hovered = true;
}

void Cell::unhover()
{
	hovered = false;
}

bool Cell::isBeingHovered()
{
	return hovered;
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

void Cell::initializeNeighbors(
	bool leftTop, 
	bool leftCenter, 
	bool leftBottom, 
	bool top, 
	bool bottom, 
	bool rightTop, 
	bool rightCenter, 
	bool rightBottom)
{
	existingNeighbors.leftTop = leftTop;
	existingNeighbors.leftCenter = leftCenter;
	existingNeighbors.leftBottom = leftBottom;
	existingNeighbors.top = top;
	existingNeighbors.bottom = bottom;
	existingNeighbors.rightTop = rightTop;
	existingNeighbors.rightCenter = rightCenter;
	existingNeighbors.rightBottom = rightBottom;

	totalNeighbors = leftTop + leftCenter + leftBottom + top + bottom +
		rightTop + rightCenter + rightBottom;
}

bool Cell::neighborExists(int offsetRow, int offsetCol)
{
	if (offsetRow == -1 && offsetCol == -1)
	{
		return existingNeighbors.leftTop;
	}
	else if (offsetRow == 0 && offsetCol == -1)
	{
		return existingNeighbors.leftCenter;
	}
	else if (offsetRow == 1 && offsetCol == -1)
	{
		return existingNeighbors.leftBottom;
	}
	else if (offsetRow == -1 && offsetCol == 0)
	{
		return existingNeighbors.top;
	}
	else if (offsetRow == 1 && offsetCol == 0)
	{
		return existingNeighbors.bottom;
	}
	else if (offsetRow == -1 && offsetCol == 1)
	{
		return existingNeighbors.rightTop;
	}
	else if (offsetRow == 0 && offsetCol == 1)
	{
		return existingNeighbors.rightCenter;
	}
	else if (offsetRow == 1 && offsetCol == 1)
	{
		return existingNeighbors.rightBottom;
	}
	else
	{
		return false;
	}

}

unsigned int Cell::getTotalNeighbors()
{
	return totalNeighbors;
}

void Cell::toggleMark()
{
	switch (mark)
	{
	case Cell::markType::none:
		mark = Cell::markType::flag;
		break;
	case Cell::markType::flag:
		mark = Cell::markType::question;
		break;
	case Cell::markType::question:
		mark = Cell::markType::none;
		break;
	default:
		break;
	}
}

bool Cell::markIsFlag()
{
	bool isFlag =
		(mark == Cell::markType::flag) ||
		(this->markIsSaved());
	//return (mark == Cell::markType::flag);
	return isFlag;
}

bool Cell::markIsSaved()
{
	return (mark == Cell::markType::saved);
}

bool Cell::markIsQuestion()
{
	return (mark == Cell::markType::question);
}

bool Cell::markIsNone()
{
	return (mark == Cell::markType::none);
}
