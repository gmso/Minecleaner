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
			cells.at(r).at(c).initializeNeighbors(
				(r != 0) && (c != 0),
				(c != 0),
				(r != rows - 1) && (c != 0),
				(r != 0),
				(r != rows - 1),
				(r != 0) && (c != cols - 1),
				(c != cols - 1),
				(r != rows - 1) && (c != cols - 1)
				);

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

void MinecleanerBoard::draw(sf::RenderWindow& window, bool showMines)
{
	for (size_t r = 0; r < config::game_cellsVertical; r++)
	{
		for (size_t c = 0; c < config::game_cellsHorizontal; c++)
		{
			drawCell(window, r, c, showMines);

			if (cells.at(r).at(c).isRevealed())
			{
				if (showMines && cells.at(r).at(c).hasMine())
				{
					// draw mine
				}
				else if (
					cells.at(r).at(c).isRevealed() &&
					cells.at(r).at(c).isNumber())
				{
					drawNumber(window, r, c);
				}
			}
			else
			{
				drawMark(window, r, c);
			}
		}
	}
	
	
}

void MinecleanerBoard::drawCell(sf::RenderWindow& window, size_t r,	size_t c, bool showMines)
{
	sf::RectangleShape shape_cell = assets::shapes_cell_closed;
	if (showMines && cells.at(r).at(c).hasMine())
	{
		shape_cell = assets::shapes_cell_openedWithMine;
	}
	else if (cells.at(r).at(c).isRevealed())
	{
		shape_cell = assets::shapes_cell_opened;
	}

	shape_cell.setPosition(
		config::game_cellSizeSide * c + config::game_paddingCell,
		config::game_cellSizeSide * r + config::game_paddingCell
	);

	window.draw(shape_cell);
}

void MinecleanerBoard::drawNumber(sf::RenderWindow& window, size_t r,size_t c)
{
	sf::Text text = assets::cellNumber;
	text.setPosition(
		config::game_cellSizeSide * c + config::game_paddingCell + config::game_cellSizeSide * 0.27,
		config::game_cellSizeSide * r + config::game_paddingCell + config::game_cellSizeSide * 0.07
	);
	switch (cells.at(r).at(c).getAdjacentBombs())
	{
	case 1:
		text.setString("1");
		text.setFillColor(assets::color_blue);
		break;
	case 2:
		text.setString("2");
		text.setFillColor(assets::color_green);
		break;
	case 3:
		text.setString("3");
		text.setFillColor(assets::color_red);
		break;
	case 4:
		text.setString("4");
		text.setFillColor(assets::color_blue_dark);
		break;
	case 5:
		text.setString("5");
		text.setFillColor(assets::color_maroon);
		break;
	case 6:
		text.setString("6");
		text.setFillColor(assets::color_cyan);
		break;
	case 7:
		text.setString("7");
		text.setFillColor(assets::color_green_dark);
		break;
	default:
		text.setString("8");
		text.setFillColor(assets::color_orange);
		break;
	}
	window.draw(text);
}

void MinecleanerBoard::drawMark(sf::RenderWindow& window, size_t r, size_t c)
{
	if (cells.at(r).at(c).markIsFlag())
	{
		sf::RectangleShape pole = assets::shapes_flag_pole;
		sf::CircleShape flag = assets::shapes_flag_flag;
		sf::CircleShape flagBorder = assets::shapes_flag_flagBorder;

		pole.setPosition(
			config::game_cellSizeSide * c + config::game_paddingCell + config::game_cellSizeSide * 0.42,
			config::game_cellSizeSide * r + config::game_paddingCell + config::game_cellSizeSide * 0.2
		);
		flag.setPosition(
			config::game_cellSizeSide * c + config::game_paddingCell + config::game_cellSizeSide * 0.18,
			config::game_cellSizeSide * r + config::game_paddingCell + config::game_cellSizeSide * 0.5
		);
		flagBorder.setPosition(
			config::game_cellSizeSide * c + config::game_paddingCell + config::game_cellSizeSide * 0.1,
			config::game_cellSizeSide * r + config::game_paddingCell + config::game_cellSizeSide * 0.57
		);

		window.draw(pole);
		window.draw(flagBorder);
		window.draw(flag);
	}
	else if (cells.at(r).at(c).markIsQuestion())
	{
		sf::Text text = assets::questionMark;
		text.setPosition(
			config::game_cellSizeSide * c + config::game_paddingCell + config::game_cellSizeSide * 0.27,
			config::game_cellSizeSide * r + config::game_paddingCell + config::game_cellSizeSide * 0.07
		);
		window.draw(text);
	}
}

bool MinecleanerBoard::processLeftClick(int x, int y)
{
	const unsigned int colClicked = x / config::game_cellSizeSide;
	const unsigned int rowClicked = y / config::game_cellSizeSide;

	const auto wasRevealed = cells.at(rowClicked).at(colClicked).isRevealed();
	const auto wasEmpty = cells.at(rowClicked).at(colClicked).isEmpty();
	const auto wasNumber = cells.at(rowClicked).at(colClicked).isNumber();
	const auto wasFlagged= cells.at(rowClicked).at(colClicked).markIsFlag();
	
	if (colClicked >= config::game_cellsHorizontal ||
		rowClicked >= config::game_cellsVertical ||
		(wasRevealed && wasEmpty) ||
		wasFlagged)
	{
		return false; //click ignored: game continues
	}
	if (cells.at(rowClicked).at(colClicked).reveal())
	{
		//Clicked on cell with mine
		return true;
	}
	else
	{
		//Clicked on cell without mine
		if (wasEmpty)
		{
			propagateClickEmptyCell(rowClicked, colClicked);
			return false;
		}
		else if (wasNumber && wasRevealed)
		{
			return (propagateClickNumberedCell(rowClicked, colClicked));
		}
		return false;
	}
}

void MinecleanerBoard::propagateClickEmptyCell(unsigned int row, unsigned int col)
{
	if (cells.at(row).at(col).reveal())
	{
		//ERROR: Mine should not be present in adjacent cell!
	}
	else
	{
		for (int adjRow = -1; adjRow < 2; adjRow++)
		{
			for (int adjCol = -1; adjCol < 2; adjCol++)
			{
				if (
					//(adjRow != 0) && (adjCol != 0) && //skip this cell
					(cells.at(row).at(col).neighborExists(adjRow,adjCol)) &&
					!(cells.at(row + adjRow).at(col + adjCol).isRevealed())//skip revealed cells
					)  
				{
					if (cells.at(row + adjRow).at(col + adjCol).isEmpty())
					{
						propagateClickEmptyCell(row + adjRow, col + adjCol);
					}
					else //if (cells.at(row + adjRow).at(col + adjCol).isNumber())
					{
						cells.at(row + adjRow).at(col + adjCol).reveal();
					}
				}
			}
		}
	}
}

bool MinecleanerBoard::propagateClickNumberedCell(unsigned int row, unsigned int col)
{
	if (!(allAdjacentMinesAreMarked(row,col)))
	{
		return false;
	}
	unsigned int accumulator = 0;

	for (int adjRow = -1; adjRow < 2; adjRow++)
	{
		for (int adjCol = -1; adjCol < 2; adjCol++)
		{
			if (
				!(adjRow == 0 && adjCol == 0) && //skip clicked cell
				(cells.at(row).at(col).neighborExists(adjRow, adjCol)) && //ignore existing neighbors
				!(cells.at(row + adjRow).at(col + adjCol).isRevealed()) && //skip revealed cells
				!(cells.at(row + adjRow).at(col + adjCol).markIsFlag()) //skip flagged cells
				)
			{
				if (cells.at(row + adjRow).at(col + adjCol).reveal())
				{
					accumulator++;
				}
				if (cells.at(row + adjRow).at(col + adjCol).isEmpty())
				{
					propagateClickEmptyCell(row + adjRow, col + adjCol);
				}
			}
		}
	}
	return (accumulator > 0);
}

bool MinecleanerBoard::allAdjacentMinesAreMarked(unsigned int row, unsigned int col)
{
	/*auto accumulator = cells.at(row).at(col).getAdjacentBombs() * 0;

	for (int adjRow = -1; adjRow < 2; adjRow++)
	{
		for (int adjCol = -1; adjCol < 2; adjCol++)
		{
			if (
				!(adjRow == 0 && adjCol == 0) && //skip clicked cell
				(cells.at(row).at(col).neighborExists(adjRow, adjCol)) &&
				!(cells.at(row + adjRow).at(col + adjCol).isRevealed())//skip revealed cells
				)
			{
				if (cells.at(row + adjRow).at(col + adjCol).markIsFlag())
				{
					accumulator++;
				}
			}
		}
	}
	*/
	return (getAdjacentFlags(row,col) == cells.at(row).at(col).getAdjacentBombs());
}

unsigned int MinecleanerBoard::getAdjacentFlags(unsigned int row, unsigned int col)
{
	auto accumulator = cells.at(row).at(col).getAdjacentBombs() * 0;

	for (int adjRow = -1; adjRow < 2; adjRow++)
	{
		for (int adjCol = -1; adjCol < 2; adjCol++)
		{
			if (
				!(adjRow == 0 && adjCol == 0) && //skip clicked cell
				(cells.at(row).at(col).neighborExists(adjRow, adjCol)) &&
				!(cells.at(row + adjRow).at(col + adjCol).isRevealed())//skip revealed cells
				)
			{
				if (cells.at(row + adjRow).at(col + adjCol).markIsFlag())
				{
					accumulator++;
				}
			}
		}
	}

	return accumulator;
}

void MinecleanerBoard::flagAllNeighbors(unsigned int row, unsigned int col)
{
	for (int adjRow = -1; adjRow < 2; adjRow++)
	{
		for (int adjCol = -1; adjCol < 2; adjCol++)
		{
			if (
				!(adjRow == 0 && adjCol == 0) && //skip clicked cell
				(cells.at(row).at(col).neighborExists(adjRow, adjCol)) &&
				!(cells.at(row + adjRow).at(col + adjCol).isRevealed()) && //skip revealed cells
				(cells.at(row + adjRow).at(col + adjCol).markIsNone())
				)
			{
				cells.at(row + adjRow).at(col + adjCol).toggleMark();
			}
		}
	}
}

unsigned int MinecleanerBoard::getAdjacentHiddenCells(unsigned int row, unsigned int col)
{
	unsigned int accumulator = 0;

	for (int adjRow = -1; adjRow < 2; adjRow++)
	{
		for (int adjCol = -1; adjCol < 2; adjCol++)
		{
			if (
				!(adjRow == 0 && adjCol == 0) && //skip clicked cell
				(cells.at(row).at(col).neighborExists(adjRow, adjCol)) &&
				!(cells.at(row + adjRow).at(col + adjCol).isRevealed())//skip revealed cells
				)
			{
				//if (cells.at(row + adjRow).at(col + adjCol).markIsFlag())
				//{
					accumulator++;
				//}
			}
		}
	}

	return accumulator;
}

void MinecleanerBoard::processRightClick(int x, int y)
{
	const unsigned int colClicked = x / config::game_cellSizeSide;
	const unsigned int rowClicked = y / config::game_cellSizeSide;

	if (colClicked >= config::game_cellsHorizontal ||
		rowClicked >= config::game_cellsVertical /*||
		cells.at(rowClicked).at(colClicked).isRevealed()*/)
	{
		return; //click ignored: game continues
	}

	if (cells.at(rowClicked).at(colClicked).isRevealed() &&
		cells.at(rowClicked).at(colClicked).isNumber())
	{
		if (getAdjacentHiddenCells(rowClicked,colClicked) ==
			cells.at(rowClicked).at(colClicked).getAdjacentBombs())
		{
			flagAllNeighbors(rowClicked, colClicked);
		}
	}
	else
	{
		cells.at(rowClicked).at(colClicked).toggleMark();
	}
	
}