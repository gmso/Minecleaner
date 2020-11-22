#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Cell.h"

class MinecleanerBoard
{
public:
	MinecleanerBoard();
	~MinecleanerBoard();

	void draw(sf::RenderWindow& window, bool showMines = false);
	void drawCell(
		sf::RenderWindow& window,
		size_t r,
		size_t c,
		bool showMines);
	void drawNumber(
		sf::RenderWindow& window,
		size_t r,
		size_t c);
	void drawMark(
		sf::RenderWindow& window,
		size_t r,
		size_t c);
	
	enum class leftClickResult
	{
		NoMine,Mine,CellsCleared
	};

	leftClickResult processLeftClick(int x, int y);
	void processRightClick(int x, int y);

	void processMousePosition(int x, int y);

	void reset();

private:
	std::vector<std::vector<Cell>> cells;
	unsigned int bombsTotal;
	unsigned int revealedCells;

	void initialize(unsigned int h, unsigned int w);
	void hideAllCells();
	void propagateClickEmptyCell(unsigned int row, unsigned int col);
	bool propagateClickNumberedCell(unsigned int row, unsigned int col);

	bool boardHasBeenCleared();

	bool allAdjacentMinesAreMarked(unsigned int row, unsigned int col);
	unsigned int getAdjacentFlags(unsigned int row, unsigned int col);
	void flagAllNeighbors(unsigned int row, unsigned int col);
	
	unsigned int getAdjacentHiddenCells(unsigned int row, unsigned int col);
};
