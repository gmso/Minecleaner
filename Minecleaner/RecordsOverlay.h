#pragma once

#include <SFML/Graphics.hpp>
#include "assets.h"
#include "Button.h"

class RecordsOverlay
{
public:
	RecordsOverlay();
	~RecordsOverlay();

	void draw(sf::RenderWindow& window);

	void processMousePosition(int x, int y);
	bool processLeftClick(int x, int y);

	void display(std::vector<unsigned long> records);
	void hide();
	bool isDisplayed();

	void updatePosition(unsigned int newGameMode);

private:
	bool displayed;
	int posX;
	int posY;
	int posX_BR;
	int posY_BR;
	std::vector<unsigned long> lastValidRecords;

	Button btnClose = Button::Button(
		config::window_width_easy / 2 + ((config::window_width_easy - 100) / 2) - 45,
		config::window_height_easy / 2 - ((config::window_height_easy - 10) / 2) + 10,
		"x", config::pixelCharSize_small,
		assets::color_red, assets::color_grey_dark, assets::color_grey_light);

	std::vector<sf::RectangleShape> recordsTable;
	std::vector<sf::CircleShape> recordsTable_Circle;
	std::vector<sf::ConvexShape> recordsTable_Convex;
	sf::CircleShape localFlagShape;
	void initializeRecordsTable();

	std::vector<sf::Text> textOfTable;
	void initializeTextOfTable();

	template <class T>
	std::string timeAsStr(T timeInMs);
};
