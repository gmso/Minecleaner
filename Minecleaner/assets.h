#pragma once

#include <SFML/Graphics.hpp>

struct assets
{
	assets();

	static sf::Color color_white;
	static sf::Color color_grey_lightest;
	static sf::Color color_grey_light;
	static sf::Color color_grey_medium;
	static sf::Color color_grey_dark;
	static sf::Color color_grey_darkest;
	static sf::Color color_black;
	static sf::Color color_red;

	static sf::RectangleShape shapes_cell_closed;
	static sf::RectangleShape shapes_cell_opened;
	static sf::RectangleShape shapes_cell_openedWithMine;

	static void intialize();
};