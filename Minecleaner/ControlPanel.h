#pragma once

#include "assets.h"
#include <SFML/Graphics.hpp>

class ControlPanel
{
public:
	ControlPanel();
	~ControlPanel();

	void draw(sf::RenderWindow& window, unsigned int gameState);

	int processLeftClick(int x, int y);
	void processMousePosition(int x, int y);

private:
	bool restartButton_hovered;
	bool restartButton_overrideUnhovered;

	void drawRestartButton(sf::RenderWindow& window, unsigned int gameState);

};