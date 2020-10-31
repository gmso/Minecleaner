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
	static sf::Color color_blue;
	static sf::Color color_green;
	static sf::Color color_blue_dark;
	static sf::Color color_maroon;
	static sf::Color color_cyan;
	static sf::Color color_green_dark;
	static sf::Color color_orange;
	static sf::Color color_red_light;

	static sf::RectangleShape shapes_cell_closed;
	static sf::RectangleShape shapes_cell_opened;
	static sf::RectangleShape shapes_cell_openedWithMine;

	static sf::CircleShape shapes_flag_flag;
	static sf::CircleShape shapes_flag_flagBorder;
	static sf::RectangleShape shapes_flag_pole;

	static sf::Font font;
	static sf::Text cellNumber;
	static sf::Text questionMark;

	static void intialize();
};