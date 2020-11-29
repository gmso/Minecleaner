#pragma once

#include <chrono>

#include <SFML/Graphics.hpp>
#include "MinecleanerBoard.h"
#include "ControlPanel.h"

class MinecleanerApp
{
public:
	MinecleanerApp();
	~MinecleanerApp();

	void draw(sf::RenderWindow& window);
	void processLeftClick(int x, int y);
	void processRightClick(int x, int y);
	void processMousePosition(int x, int y);

private:
	MinecleanerBoard board;
	ControlPanel panel;
	enum class gameState{None,Playing,Lost,Won,Restarting} currentGameState;
	void updateGameState(gameState newState);
	bool boardClickingAllowed();

	std::chrono::steady_clock::time_point timerStart;
	std::chrono::steady_clock::time_point timerEnd;
	bool timerRunning;
	void startTimer();
	void stopTimer();
	std::string getTimer();
};
