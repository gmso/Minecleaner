#include "assets.h"
#include "config.h"
#include <SFML/Graphics.hpp>
#include "MinecleanerApp.h"

sf::Color assets::color_white = sf::Color::White;
sf::Color assets::color_grey_lightest = sf::Color::Color(226, 226, 226, 255);
sf::Color assets::color_grey_light = sf::Color::Color(183, 183, 183, 255);
sf::Color assets::color_grey_medium = sf::Color::Color(147, 147, 147, 255);
sf::Color assets::color_grey_dark = sf::Color::Color(102, 102, 102, 255);
sf::Color assets::color_grey_darkest = sf::Color::Color(58, 58, 58, 255);
sf::Color assets::color_black = sf::Color::Black;
sf::Color assets::color_red = sf::Color::Color(237, 51, 14, 255);
sf::Color assets::color_blue = sf::Color::Color(14, 29, 237, 255);
sf::Color assets::color_green = sf::Color::Color(44, 170, 52, 255);
sf::Color assets::color_blue_dark = sf::Color::Color(2, 23, 127, 255);
sf::Color assets::color_maroon = sf::Color::Color(119, 19, 77, 255);
sf::Color assets::color_cyan = sf::Color::Color(23, 173, 158, 255);
sf::Color assets::color_green_dark = sf::Color::Color(8, 94, 57, 255);
sf::Color assets::color_orange= sf::Color::Color(153, 88, 13, 255);
sf::Color assets::color_red_light = sf::Color::Color(234, 82, 82, 255);

sf::RectangleShape assets::shapes_cell_closed;
sf::RectangleShape assets::shapes_cell_opened;
sf::RectangleShape assets::shapes_cell_openedWithMine;

sf::CircleShape assets::shapes_flag_flag;
sf::CircleShape assets::shapes_flag_flagBorder;
sf::RectangleShape assets::shapes_flag_pole;

sf::Font assets::font;
sf::Text assets::cellNumber;
sf::Text assets::questionMark;

assets::assets()
{
	
}

void assets::intialize()
{
	shapes_cell_closed.setSize(
		sf::Vector2f(
			config::game_cellSizeSide - 2 * config::game_paddingCell,
			config::game_cellSizeSide - 2 * config::game_paddingCell
		)
	);
	shapes_cell_opened.setSize(
		sf::Vector2f(
			config::game_cellSizeSide - 2 * config::game_paddingCell,
			config::game_cellSizeSide - 2 * config::game_paddingCell
		)
	);
	shapes_cell_openedWithMine.setSize(
		sf::Vector2f(
			config::game_cellSizeSide - 2 * config::game_paddingCell,
			config::game_cellSizeSide - 2 * config::game_paddingCell
		)
	);
	shapes_cell_closed.setFillColor(assets::color_grey_dark);
	shapes_cell_opened.setFillColor(assets::color_grey_lightest);
	shapes_cell_openedWithMine.setFillColor(assets::color_red);

	shapes_flag_flag.setRadius(config::game_cellSizeSide / 5);
	shapes_flag_flag.setPointCount(3);
	shapes_flag_flag.setFillColor(assets::color_red_light);
	shapes_flag_flag.setRotation(270);

	shapes_flag_flagBorder = assets::shapes_flag_flag;
	shapes_flag_flagBorder.setRadius(shapes_flag_flag.getRadius() * 1.4);
	shapes_flag_flagBorder.setFillColor(assets::color_grey_lightest);
		
	shapes_flag_pole.setSize(
		sf::Vector2f(
			config::game_cellSizeSide * 0.1, 
			config::game_cellSizeSide * 0.6)
		);
	shapes_flag_pole.setFillColor(assets::color_grey_lightest);

	if (!font.loadFromFile("segoeui.ttf"))
	{
		// error...
	}
	cellNumber.setFont(font);
	cellNumber.setString("1");
	cellNumber.setCharacterSize(24); // in pixels, not points!
	cellNumber.setFillColor(assets::color_grey_darkest);

	questionMark.setFont(font);
	questionMark.setString("?");
	questionMark.setCharacterSize(24); // in pixels, not points!
	questionMark.setFillColor(assets::color_grey_lightest);
	questionMark.setStyle(sf::Text::Bold);
}
