#include "MinecleanerBoard.h"
#include "config.h"
#include "assets.h"

MinecleanerBoard::MinecleanerBoard()
{
	cells.resize(
		config::game_cellsVertical,
		std::vector<Cell>(config::game_cellsHorizontal));
	initialize(config::game_cellsVertical, config::game_cellsHorizontal);
}

MinecleanerBoard::~MinecleanerBoard()
{
}

void MinecleanerBoard::initialize(unsigned int rows, unsigned int cols)
{
	bombsTotal = 
		std::rand() % (config::game_bombsMaximum - config::game_bombsMinimum) +
		config::game_bombsMinimum;
	unsigned int bombsLeft = bombsTotal;
	while (bombsLeft > 0)
	{
		unsigned int randomRow = std::rand() % rows;
		unsigned int randomCol = std::rand() % cols;
		if (!(cells.at(randomRow).at(randomCol).hasMine()))
		{
			cells.at(randomRow).at(randomCol).addMine();
			--bombsLeft;
		}
	}

	for (size_t r = 0; r < rows; r++)
	{
		for (size_t c = 0; c < cols; c++)
		{
			if (!(cells.at(r).at(c).hasMine()))
			{
				const unsigned int leftTop = 
					(r == 0) || (c == 0) ? 
					0 : 
					cells.at(r - 1).at(c - 1).hasMine();
				const unsigned int leftCenter =
					(c == 0) ?
					0 :
					cells.at(r).at(c - 1).hasMine();
				const unsigned int leftBottom =
					(r == rows - 1) || (c == 0) ?
					0 :
					cells.at(r + 1).at(c - 1).hasMine();
				const unsigned int top =
					(r == 0) ?
					0 :
					cells.at(r - 1).at(c).hasMine();
				const unsigned int bottom =
					(r == rows - 1) ?
					0 :
					cells.at(r + 1).at(c).hasMine();
				const unsigned int rightTop =
					(r == 0) || (c == cols - 1) ?
					0 :
					cells.at(r - 1).at(c + 1).hasMine();
				const unsigned int rightCenter =
					(c == cols - 1) ?
					0 :
					cells.at(r).at(c + 1).hasMine();
				const unsigned int rightBottom =
					(r == rows - 1) || (c == cols - 1) ?
					0 :
					cells.at(r + 1).at(c + 1).hasMine();

				cells.at(r).at(c).addNumber(leftTop , leftCenter , leftBottom ,
					top , bottom ,rightTop , rightCenter , rightBottom);
			}

		}
	}
}

void MinecleanerBoard::draw(sf::RenderWindow& window)
{
	for (size_t r = 0; r < config::game_cellsVertical; r++)
	{
		for (size_t c = 0; c < config::game_cellsHorizontal; c++)
		{
			assets::shapes_cell_closed.setPosition(
				config::game_cellSizeSide * c + config::game_paddingCell,
				config::game_cellSizeSide * r + config::game_paddingCell
			);
			window.draw(assets::shapes_cell_closed);
		}
	}
	
	
}