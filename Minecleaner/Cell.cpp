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
