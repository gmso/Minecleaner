#pragma once

#include "assets.h"
#include "Button.h"
#include <SFML/Graphics.hpp>

class ControlPanel
{
public:
	ControlPanel();
	~ControlPanel();

	void draw(
		sf::RenderWindow& window, 
		unsigned int gameState, 
		unsigned int clicks,
		std::string timePlayed,
		unsigned int livesRemaining
	);

	enum class gameDifficulty { Easy, Medium, Hard };
	gameDifficulty getDifficulty();

	gameDifficulty processLeftClick(int x, int y);
	void processMousePosition(int x, int y);

private:
	bool restartButton_hovered;
	bool restartButton_overrideUnhovered;
	gameDifficulty difficulty;

	Button btnEasy = Button::Button(20,
		config::controlPanel_height / 20 * 4,
		"E", config::pixelCharSize_small,
		assets::color_blue_dark, assets::color_grey_light, assets::color_grey_dark);

	Button btnMedium = Button::Button(57,
		config::controlPanel_height / 20 * 4,
		"M", config::pixelCharSize_small,
		assets::color_orange, assets::color_grey_light, assets::color_grey_dark);

	Button btnHard = Button::Button(94,
		config::controlPanel_height / 20 * 4,
		"H", config::pixelCharSize_small,
		assets::color_red_dark, assets::color_grey_light, assets::color_grey_dark);

	void drawRestartButton(sf::RenderWindow& window, unsigned int gameState);
	void drawClickCounter(sf::RenderWindow& window, unsigned int clicks);
	void drawTimer(sf::RenderWindow& window, std::string timePlayed);
	void drawStatusBar(sf::RenderWindow& window, unsigned int gameState);
	void drawGameModes(sf::RenderWindow& window);
	void drawLivesRemaining(sf::RenderWindow& window, unsigned int livesRemaining);

	gameDifficulty toggleGameMode(
		Button::State Easy, Button::State Medium, Button::State Hard);
};