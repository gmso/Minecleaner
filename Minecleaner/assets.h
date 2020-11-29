#pragma once

#include <SFML/Graphics.hpp>

struct assets
{
	assets();

	static sf::Color color_white;
	static sf::Color color_grey_lightest;
	static sf::Color color_grey_light;
	static sf::Color color_grey_medium;
	static sf::Color color_grey_medium_dark;
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
	static sf::Color color_green_light;
	static sf::Color color_green_medium;

	static sf::RectangleShape shapes_cell_closed;
	static sf::RectangleShape shapes_cell_opened;
	static sf::RectangleShape shapes_cell_openedWithMine;
	static sf::RectangleShape shapes_cell_hovered;
	static sf::RectangleShape shapes_cell_openedWithMine_gameWon;

	static sf::CircleShape shapes_flag_flag;
	static sf::CircleShape shapes_flag_flagBorder;
	static sf::RectangleShape shapes_flag_pole;

	static sf::CircleShape shapes_mine_body;
	static sf::RectangleShape shapes_mine_points_1;
	static sf::RectangleShape shapes_mine_points_2;
	static sf::RectangleShape shapes_mine_points_3;
	static sf::RectangleShape shapes_mine_points_4;

	static sf::ConvexShape shapes_pointer_arrow;
	static sf::RectangleShape shapes_pointer_arrowTail;
	static sf::RectangleShape shapes_pointer_line;


	static unsigned int shapes_button_restart_upperLeft_X;
	static unsigned int shapes_button_restart_upperLeft_Y;
	static unsigned int shapes_button_restart_lowerRight_X;
	static unsigned int shapes_button_restart_lowerRight_Y;
	static sf::RectangleShape shapes_button_restart;
	static sf::RectangleShape shapes_button_restart_border;

	static sf::Font font;
	static sf::Text cellNumber;
	static sf::Text questionMark;
	static sf::Text restartButton;
	static sf::Text clickCounter;

	static void intialize();

	static void restartButton_hovered();
	static void restartButton_notHovered();
	static void restartButton_gameWon();
	static void restartButton_gameLost();

	static void clickCounter_update(unsigned int count);

};