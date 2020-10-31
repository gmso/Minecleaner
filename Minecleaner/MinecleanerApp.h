#pragma once

#include <SFML/Graphics.hpp>
#include "MinecleanerBoard.h"

class MinecleanerApp
{
public:
	MinecleanerApp();
	~MinecleanerApp();

	void draw(sf::RenderWindow& window);
	void processLeftClick(int x, int y);
	void processRightClick(int x, int y);

	//bool isRunning();
	//void processEvent(sf::Event& event);
private:
	//sf::RenderWindow window;
	MinecleanerBoard board;
	enum class gameState{None,Playing,Lost,Won} currentGameState;
};
