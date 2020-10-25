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
	srand(time(0));	//randomize seed for rand()
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
			sf::RectangleShape shape_cell =
				cells.at(r).at(c).isRevealed() ?
				(cells.at(r).at(c).hasMine() ?
					assets::shapes_cell_openedWithMine :
					assets::shapes_cell_opened)	:
				assets::shapes_cell_closed;

			shape_cell.setPosition(
				config::game_cellSizeSide * c + config::game_paddingCell,
				config::game_cellSizeSide * r + config::game_paddingCell
			);
			window.draw(shape_cell);
		}
	}
	
	
}

bool MinecleanerBoard::processLeftClick(int x, int y)
{
	unsigned int colClicked = x / config::game_cellSizeSide;
	unsigned int rowClicked = y / config::game_cellSizeSide;
	
	if (colClicked > config::game_cellsHorizontal ||
		rowClicked > config::game_cellsVertical)
	{
		return true; //click ignored: game continues
	}
	if (cells.at(rowClicked).at(colClicked).reveal())
	{
		//Clicked on cell with mine
		return false;
	}
	else
	{
		//Clicked on cell without mine
		return true;
	}

}
