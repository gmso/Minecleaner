#include "MinecleanerBoard.h"
#include "config.h"
#include "assets.h"

MinecleanerBoard::MinecleanerBoard()
{
	cells.resize(
		config::game_cellsVertical,
		std::vector<Cell>(config::game_cellsHorizontal));
	initialize(config::game_cellsVertical, config::game_cellsHorizontal);
	validClicks = 0;
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

void MinecleanerBoard::hideAllCells()
{
	for (size_t r = 0; r < config::game_cellsVertical; r++)
	{
		for (size_t c = 0; c < config::game_cellsHorizontal; c++)
		{
			cells.at(r).at(c).hide();
		}
	}
}

void MinecleanerBoard::draw(
	sf::RenderWindow& window, 
	bool showMines_lost,
	bool showMines_won
	)
{
	for (size_t r = 0; r < config::game_cellsVertical; r++)
	{
		for (size_t c = 0; c < config::game_cellsHorizontal; c++)
		{
			drawCell(window, r, c, showMines_lost, showMines_won);

			if ((showMines_lost || showMines_won) &&
				cells.at(r).at(c).hasMine() &&
				!cells.at(r).at(c).markIsFlag())
			{
				drawMine(window, r, c, showMines_lost, showMines_won);
			}

			if (cells.at(r).at(c).isRevealed())
			{
				if (cells.at(r).at(c).isNumber())
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

void MinecleanerBoard::drawCell(
	sf::RenderWindow& window, 
	size_t r,	
	size_t c, 
	bool showMines_lost,
	bool showMines_won)
{
	sf::RectangleShape shape_cell = assets::shapes_cell_closed;
	if (showMines_lost && cells.at(r).at(c).hasMine())
	{
		shape_cell = assets::shapes_cell_openedWithMine;
	}
	else if (showMines_won && cells.at(r).at(c).hasMine())
	{
		shape_cell = assets::shapes_cell_openedWithMine_gameWon;
	}
	else if (cells.at(r).at(c).isRevealed())
	{
		shape_cell = assets::shapes_cell_opened;
	}
	else if (cells.at(r).at(c).isBeingHovered())
	{
		shape_cell = assets::shapes_cell_hovered;
	}

	shape_cell.setPosition(
		config::game_cellSizeSide * c + config::game_paddingCell,
		config::game_cellSizeSide * r + config::game_paddingCell + config::game_offsetBoard_y
	);

	window.draw(shape_cell);
}

void MinecleanerBoard::drawMine(
	sf::RenderWindow& window,
	size_t r,
	size_t c,
	bool showMines_lost,
	bool showMines_won)
{
	sf::CircleShape mine = assets::shapes_mine_body;
	sf::RectangleShape bar_1 = assets::shapes_mine_points_1;
	sf::RectangleShape bar_2 = assets::shapes_mine_points_2;
	sf::RectangleShape bar_3 = assets::shapes_mine_points_3;
	sf::RectangleShape bar_4 = assets::shapes_mine_points_4;

	mine.setPosition(
		config::game_cellSizeSide * c + config::game_paddingCell + config::game_cellSizeSide * 0.225,
		config::game_cellSizeSide * r + config::game_paddingCell + config::game_cellSizeSide * 0.225
		+ config::game_offsetBoard_y
	);
	bar_1.setPosition(
		config::game_cellSizeSide * c + config::game_paddingCell + config::game_cellSizeSide * 0.4,
		config::game_cellSizeSide * r + config::game_paddingCell + config::game_cellSizeSide * 0.15
		+ config::game_offsetBoard_y
	);
	bar_2.setPosition(
		config::game_cellSizeSide * c + config::game_paddingCell + config::game_cellSizeSide * 0.65,
		config::game_cellSizeSide * r + config::game_paddingCell + config::game_cellSizeSide * 0.2
		+ config::game_offsetBoard_y
	);
	bar_3.setPosition(
		config::game_cellSizeSide * c + config::game_paddingCell + config::game_cellSizeSide * 0.75,
		config::game_cellSizeSide * r + config::game_paddingCell + config::game_cellSizeSide * 0.4
		+ config::game_offsetBoard_y
	);
	bar_4.setPosition(
		config::game_cellSizeSide * c + config::game_paddingCell + config::game_cellSizeSide * 0.7,
		config::game_cellSizeSide * r + config::game_paddingCell + config::game_cellSizeSide * 0.62
		+ config::game_offsetBoard_y
	);

	if (showMines_won)
	{
		mine.setFillColor(assets::color_grey_lightest);
		bar_1.setFillColor(assets::color_grey_lightest);
		bar_2.setFillColor(assets::color_grey_lightest);
		bar_3.setFillColor(assets::color_grey_lightest);
		bar_4.setFillColor(assets::color_grey_lightest);
	}

	window.draw(mine);
	window.draw(bar_1);
	window.draw(bar_2);
	window.draw(bar_3);
	window.draw(bar_4);
}

void MinecleanerBoard::drawNumber(sf::RenderWindow& window, size_t r,size_t c)
{
	sf::Text text = assets::cellNumber;
	text.setPosition(
		config::game_cellSizeSide * c + config::game_paddingCell + config::game_cellSizeSide * 0.27,
		config::game_cellSizeSide * r + config::game_paddingCell + config::game_cellSizeSide * 0.07 + 
			config::game_offsetBoard_y
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
				+ config::game_offsetBoard_y
		);
		flag.setPosition(
			config::game_cellSizeSide * c + config::game_paddingCell + config::game_cellSizeSide * 0.18,
			config::game_cellSizeSide * r + config::game_paddingCell + config::game_cellSizeSide * 0.5
				+ config::game_offsetBoard_y
		);
		flagBorder.setPosition(
			config::game_cellSizeSide * c + config::game_paddingCell + config::game_cellSizeSide * 0.1,
			config::game_cellSizeSide * r + config::game_paddingCell + config::game_cellSizeSide * 0.57
				+ config::game_offsetBoard_y
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
				+ config::game_offsetBoard_y
		);
		window.draw(text);
	}
}

MinecleanerBoard::leftClickResult MinecleanerBoard::processLeftClick(int x, int y)
{
	const unsigned int colClicked = x / config::game_cellSizeSide;
	const unsigned int rowClicked = y / config::game_cellSizeSide;

	const auto wasRevealed = cells.at(rowClicked).at(colClicked).isRevealed();
	const auto wasEmpty = cells.at(rowClicked).at(colClicked).isEmpty();
	const auto wasNumber = cells.at(rowClicked).at(colClicked).isNumber();
	const auto wasFlagged= cells.at(rowClicked).at(colClicked).markIsFlag();
	
	MinecleanerBoard::leftClickResult clickResult = MinecleanerBoard::leftClickResult::NoMine;
	if (colClicked >= config::game_cellsHorizontal ||
		rowClicked >= config::game_cellsVertical ||
		(wasRevealed && wasEmpty) ||
		wasFlagged)
	{
		//click ignored: game continues
	}
	else 
	{
		validClicks += 1;
		if (cells.at(rowClicked).at(colClicked).reveal())
		{
			//Clicked on cell with mine
			clickResult = MinecleanerBoard::leftClickResult::Mine;
		}
		else
		{
			//Clicked on cell without mine
			if (wasEmpty)
			{
				propagateClickEmptyCell(rowClicked, colClicked);
				//click ignored: game continues
			}
			else if (wasNumber && wasRevealed)
			{
				if (propagateClickNumberedCell(rowClicked, colClicked))
				{
					clickResult = MinecleanerBoard::leftClickResult::Mine;
				}
			}
		}
	}

	if (boardHasBeenCleared())
	{
		return MinecleanerBoard::leftClickResult::CellsCleared;
	}
	else
	{
		return clickResult;
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

bool MinecleanerBoard::boardHasBeenCleared()
{
	unsigned int accum = 0;
	for (size_t r = 0; r < config::game_cellsVertical; r++)
	{
		for (size_t c = 0; c < config::game_cellsHorizontal; c++)
		{
			accum += cells.at(r).at(c).isRevealed();
		}
	}
	return (bombsTotal + accum == config::game_totalCells);
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

	validClicks += 1;
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

void MinecleanerBoard::processMousePosition(int x, int y)
{
	if (x >= config::game_offsetBoard_x &&
		y >= config::game_offsetBoard_y)
	{
		const unsigned int hoveredCol = std::min(
			static_cast<unsigned int>((x - config::game_offsetBoard_x) / config::game_cellSizeSide),
			config::game_cellsHorizontal - 1);
		const unsigned int hoveredRow = std::min(
			static_cast<unsigned int>((y - config::game_offsetBoard_y) / config::game_cellSizeSide),
			config::game_cellsVertical - 1);

		for (size_t r = 0; r < config::game_cellsVertical; r++)
		{
			for (size_t c = 0; c < config::game_cellsHorizontal; c++)
			{
				if (r == hoveredRow && c == hoveredCol)
				{
					cells.at(r).at(c).hover();
				}
				else
				{
					cells.at(r).at(c).unhover();
				}
			}
		}
	}
	else
	{
		for (size_t r = 0; r < config::game_cellsVertical; r++)
		{
			for (size_t c = 0; c < config::game_cellsHorizontal; c++)
			{
				cells.at(r).at(c).unhover();
			}
		}
	}
}

void MinecleanerBoard::reset()
{
	//hideAllCells();
	cells.clear();
	cells.resize(
		config::game_cellsVertical,
		std::vector<Cell>(config::game_cellsHorizontal));
	initialize(config::game_cellsVertical, config::game_cellsHorizontal);
	validClicks = 0;
}

unsigned int MinecleanerBoard::getValidClicks()
{
	return validClicks;
}
