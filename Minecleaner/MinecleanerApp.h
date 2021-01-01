#pragma once

#include <chrono>

#include <SFML/Graphics.hpp>
#include "MinecleanerBoard.h"
#include "ControlPanel.h"
#include "RecordsOverlay.h"
#include "RecordsFile.h"

class MinecleanerApp
{
public:
	MinecleanerApp();
	~MinecleanerApp();

	void draw(sf::RenderWindow& window);
	void processLeftClick(int x, int y, sf::RenderWindow& window);
	void processRightClick(int x, int y);
	void processMousePosition(int x, int y);

	ControlPanel::gameDifficulty getGameDifficulty() const { return currentDificulty; }

private:
	MinecleanerBoard board;
	ControlPanel panel;
	RecordsOverlay recordsOverlay;
	RecordsFile myRecordsFile;
	enum class gameState{
		None,Playing,Lost,Won,Restarting,ViewingRecords} currentGameState;
	gameState gameStateBeforeRecordsOverlay;
	ControlPanel::gameDifficulty currentDificulty;
	unsigned int livesRemaining;

	void restartGame();
	void updateGameState(gameState newState);
	bool boardClickingAllowed();
	bool panelClickingAllowed();
	void resizeWindow(
		sf::RenderWindow& win,
		ControlPanel::gameDifficulty newDiff
	);
	void showRecords();
	void hideRecords();

	std::chrono::steady_clock::time_point timerStart;
	std::chrono::steady_clock::time_point timerEnd;
	bool timerRunning;
	void startTimer();
	void stopTimer();
	std::string getTimer();
};
