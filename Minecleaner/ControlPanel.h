#pragma once

#include "assets.h"
#include <SFML/Graphics.hpp>

class ControlPanel
{
public:
	ControlPanel();
	~ControlPanel();

	void draw(sf::RenderWindow& window);

	int processLeftClick(int x, int y);
	void processMousePosition(int x, int y);

private:
	bool restartButton_hovered;

	void drawRestartButton(sf::RenderWindow& window);

};