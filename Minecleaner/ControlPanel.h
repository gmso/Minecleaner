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

private:


	void drawRestartButton(sf::RenderWindow& window);

};