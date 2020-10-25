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
	bool processLeftClick(int x, int y);
private:
	std::vector<std::vector<Cell>> cells;
	unsigned int bombsTotal;

	void initialize(unsigned int h, unsigned int w);
};
