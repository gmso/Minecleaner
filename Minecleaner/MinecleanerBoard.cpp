#include "MinecleanerBoard.h"
#include "config.cpp"

MinecleanerBoard::MinecleanerBoard()
{
	cells.resize(
		config::game::cellsHorizontal, 
		std::vector<Cell>(config::game::cellsVertical));
	initialize(config::game::cellsHorizontal, config::game::cellsVertical);
}

MinecleanerBoard::~MinecleanerBoard()
{
}

void MinecleanerBoard::initialize(unsigned int cols, unsigned int rows)
{
	bombsTotal = 
		std::rand() % (config::game::bombsMaximum - config::game::bombsMinimum) +
		config::game::bombsMinimum;
	unsigned int bombsLeft = bombsTotal;
	while (bombsLeft > 0)
	{
		unsigned int randomCol = std::rand() % cols;
		unsigned int randomRow = std::rand() % rows;
		if (!(cells.at(randomCol).at(randomRow).hasMine()))
		{
			cells.at(randomCol).at(randomRow).addMine();
			--bombsLeft;
		}
	}

	for (size_t i = 0; i < rows; i++)
	{
		std::transform(
			cells.at(i).begin(),
			cells.at(i).end(),
			cells.at(i).begin(),
			[i](Cell c) {
				switch (i)
				{
				case 0:

					break;
				default:
					break;
				}
			}
		);
	}
}
