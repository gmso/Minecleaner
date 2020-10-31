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
	bool processLeftClick(int x, int y);
	void processRightClick(int x, int y);
private:
	std::vector<std::vector<Cell>> cells;
	unsigned int bombsTotal;

	void initialize(unsigned int h, unsigned int w);
	void propagateClickEmptyCell(unsigned int row, unsigned int col);
};
