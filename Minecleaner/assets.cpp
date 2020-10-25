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

sf::RectangleShape assets::shapes_cell_closed;
sf::RectangleShape assets::shapes_cell_opened;
sf::RectangleShape assets::shapes_cell_openedWithMine;

sf::Font assets::font;
sf::Text assets::cellNumber;

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

	if (!font.loadFromFile("segoeui.ttf"))
	{
		// error...
	}
	cellNumber.setFont(font);
	cellNumber.setString("1");
	cellNumber.setCharacterSize(24); // in pixels, not points!
	cellNumber.setFillColor(assets::color_grey_darkest);
	//cellNumber.setStyle(sf::Text::Bold);
}
