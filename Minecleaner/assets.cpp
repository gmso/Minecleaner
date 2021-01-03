#include "assets.h"
#include "config.h"
#include <SFML/Graphics.hpp>
#include "MinecleanerApp.h"

sf::Color assets::color_white = sf::Color::White;
sf::Color assets::color_grey_lightest = sf::Color::Color(226, 226, 226, 255);
sf::Color assets::color_grey_light = sf::Color::Color(183, 183, 183, 255);
sf::Color assets::color_grey_medium = sf::Color::Color(147, 147, 147, 255);
sf::Color assets::color_grey_medium_semitransparent = sf::Color::Color(147, 147, 147, 180);
sf::Color assets::color_grey_medium_dark = sf::Color::Color(125, 125, 125, 255);
sf::Color assets::color_grey_dark = sf::Color::Color(102, 102, 102, 255);
sf::Color assets::color_grey_darkest = sf::Color::Color(58, 58, 58, 255);
sf::Color assets::color_grey_darkest_semitransparent = sf::Color::Color(58, 58, 58, 220);
sf::Color assets::color_black = sf::Color::Black;
sf::Color assets::color_blue = sf::Color::Color(14, 29, 237, 255);
//sf::Color assets::color_blue_dark = sf::Color::Color(23, 32, 155, 255);
sf::Color assets::color_green = sf::Color::Color(44, 170, 52, 255);
sf::Color assets::color_blue_dark = sf::Color::Color(2, 23, 127, 255);
sf::Color assets::color_blue_dark_semitransparent = sf::Color::Color(2, 23, 127, 180);
sf::Color assets::color_maroon = sf::Color::Color(119, 19, 77, 255);
sf::Color assets::color_cyan = sf::Color::Color(23, 173, 158, 255);
sf::Color assets::color_green_dark = sf::Color::Color(8, 94, 57, 255);
sf::Color assets::color_orange = sf::Color::Color(198, 122, 35, 255);
sf::Color assets::color_orange_semitransparent = sf::Color::Color(198, 122, 35, 180);
sf::Color assets::color_red_light = sf::Color::Color(234, 82, 82, 255);
//sf::Color assets::color_red = sf::Color::Color(237, 51, 14, 255);
sf::Color assets::color_red = color_red_light;
sf::Color assets::color_red_dark = sf::Color::Color(147, 26, 26, 255);
sf::Color assets::color_red_dark_semitransparent = sf::Color::Color(147, 26, 26, 180);
sf::Color assets::color_green_light = sf::Color::Color(125, 242, 82, 255);
sf::Color assets::color_green_medium = sf::Color::Color(81, 160, 53, 255);
sf::Color assets::color_yellow = sf::Color::Color(216, 216, 67, 255);
sf::Color assets::color_yellow_semitransparent = sf::Color::Color(216, 216, 67, 120);

sf::RectangleShape assets::shapes_cell_closed;
sf::RectangleShape assets::shapes_cell_opened;
sf::RectangleShape assets::shapes_cell_openedWithMine;
sf::RectangleShape assets::shapes_cell_hovered;
sf::RectangleShape assets::shapes_cell_openedWithMine_gameWon;

sf::CircleShape assets::shapes_flag_flag;
sf::CircleShape assets::shapes_flag_flagBorder;
sf::RectangleShape assets::shapes_flag_pole;

sf::CircleShape assets::shapes_mine_body;
sf::RectangleShape assets::shapes_mine_points_1;
sf::RectangleShape assets::shapes_mine_points_2;
sf::RectangleShape assets::shapes_mine_points_3;
sf::RectangleShape assets::shapes_mine_points_4;

sf::ConvexShape assets::shapes_pointer_arrow;
sf::RectangleShape assets::shapes_pointer_arrowTail;

sf::CircleShape assets::shapes_stopclock_border;
sf::CircleShape assets::shapes_stopclock_body;
sf::RectangleShape assets::shapes_stopclock_top_1;
sf::RectangleShape assets::shapes_stopclock_top_2;
sf::RectangleShape assets::shapes_stopclock_needle;

unsigned int assets::shapes_button_restart_upperLeft_X = 0;
unsigned int assets::shapes_button_restart_upperLeft_Y = 0;
unsigned int assets::shapes_button_restart_lowerRight_X = 0;
unsigned int assets::shapes_button_restart_lowerRight_Y = 0;
sf::RectangleShape assets::shapes_button_restart;
sf::RectangleShape assets::shapes_button_restart_border;

sf::RectangleShape assets::shapes_status_bar;
sf::RectangleShape assets::shapes_status_bar_border;

sf::RectangleShape assets::shapes_records_background_overlay;
sf::RectangleShape assets::shapes_records_background_box;
sf::RectangleShape assets::shapes_records_background_box_border;


sf::Font assets::font;
sf::Text assets::cellNumber;
sf::Text assets::questionMark;
sf::Text assets::restartButton;
sf::Text assets::clickCounter;
sf::Text assets::timerCount;

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
	shapes_cell_hovered.setSize(
		sf::Vector2f(
			config::game_cellSizeSide - 2 * config::game_paddingCell,
			config::game_cellSizeSide - 2 * config::game_paddingCell
		)
	);
	shapes_cell_openedWithMine_gameWon.setSize(
		sf::Vector2f(
			config::game_cellSizeSide - 2 * config::game_paddingCell,
			config::game_cellSizeSide - 2 * config::game_paddingCell
		)
	);
	shapes_cell_closed.setFillColor(assets::color_grey_dark);
	shapes_cell_opened.setFillColor(assets::color_grey_lightest);
	shapes_cell_openedWithMine.setFillColor(assets::color_red);
	shapes_cell_hovered.setFillColor(assets::color_grey_medium_dark);
	shapes_cell_openedWithMine_gameWon.setFillColor(assets::color_green_medium);

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

	shapes_mine_body.setRadius(config::game_cellSizeSide / 4.5);
	shapes_mine_body.setPointCount(50);
	shapes_mine_body.setFillColor(assets::color_grey_darkest);

	shapes_mine_points_1.setSize(
		sf::Vector2f(
			config::game_cellSizeSide * 0.1,
			config::game_cellSizeSide * 0.6)
	);
	shapes_mine_points_1.setFillColor(assets::color_grey_darkest);

	shapes_mine_points_2 = assets::shapes_mine_points_1;
	shapes_mine_points_2.setRotation(45);

	shapes_mine_points_3 = assets::shapes_mine_points_1;
	shapes_mine_points_3.setRotation(90);

	shapes_mine_points_4 = assets::shapes_mine_points_1;
	shapes_mine_points_4.setRotation(135);

	shapes_pointer_arrow.setPointCount(3);
	shapes_pointer_arrow.setFillColor(assets::color_grey_lightest);
	shapes_pointer_arrow.setPoint(0, sf::Vector2f(0.f, 0.f));
	shapes_pointer_arrow.setPoint(1, sf::Vector2f(0.f, 20.f));
	shapes_pointer_arrow.setPoint(2, sf::Vector2f(12.f, 15.f));
	shapes_pointer_arrow.setPosition(
		config::window_width_easy * 3 / 4 - 15,
		config::controlPanel_height / 4 - 3
	);

	shapes_pointer_arrowTail.setSize(sf::Vector2f(3.f,15.f));
	shapes_pointer_arrowTail.setFillColor(assets::color_grey_lightest);
	shapes_pointer_arrowTail.setRotation(340);
	shapes_pointer_arrowTail.setPosition(
		config::window_width_easy * 3 / 4 - 12,
		config::controlPanel_height / 4 + 9
	);

	shapes_stopclock_border.setRadius(12);
	shapes_stopclock_border.setPointCount(50);
	shapes_stopclock_border.setFillColor(assets::color_grey_lightest);
	shapes_stopclock_border.setPosition(
		config::window_width_easy * 3 / 4 - 20,
		config::controlPanel_height / 4 * 2 + 12
	);

	shapes_stopclock_body.setRadius(9);
	shapes_stopclock_body.setPointCount(50);
	shapes_stopclock_body.setFillColor(assets::color_grey_medium);
	shapes_stopclock_body.setPosition(
		config::window_width_easy * 3 / 4 - 17,
		config::controlPanel_height / 4 * 2 + 15
	);

	shapes_stopclock_top_1.setSize(sf::Vector2f(3.f, 5.f));
	shapes_stopclock_top_1.setFillColor(assets::color_grey_lightest);
	shapes_stopclock_top_1.setPosition(
		config::window_width_easy * 3 / 4 - 9,
		config::controlPanel_height / 4 * 2 + 8
	);

	shapes_stopclock_top_2.setSize(sf::Vector2f(9.f, 3.f));
	shapes_stopclock_top_2.setFillColor(assets::color_grey_lightest);
	shapes_stopclock_top_2.setPosition(
		config::window_width_easy * 3 / 4 - 12,
		config::controlPanel_height / 4 * 2 + 6
	);

	shapes_stopclock_needle.setSize(sf::Vector2f(8.f, 3.f));
	shapes_stopclock_needle.setFillColor(assets::color_grey_lightest);
	shapes_stopclock_needle.setRotation(45);
	shapes_stopclock_needle.setPosition(
		config::window_width_easy * 3 / 4 - 7,
		config::controlPanel_height / 4 * 2 + 21
	);

	shapes_button_restart_upperLeft_X =
		config::window_width_easy / 2 - config::controlPanel_restartButtonBorder_width / 2 - 4;
	shapes_button_restart_upperLeft_Y =
		config::controlPanel_height / 2 - config::controlPanel_restartButtonBorder_height / 2;
	shapes_button_restart_lowerRight_X =
		shapes_button_restart_upperLeft_X + config::controlPanel_restartButtonBorder_width;
	shapes_button_restart_lowerRight_Y =
		shapes_button_restart_upperLeft_Y + config::controlPanel_restartButtonBorder_height;

	shapes_button_restart.setSize(sf::Vector2f(
		config::controlPanel_restartButton_width, 
		config::controlPanel_restartButton_height
		));
	shapes_button_restart.setPosition(
		config::window_width_easy / 2 - config::controlPanel_restartButtonBorder_width / 2,
		config::controlPanel_height / 2 - config::controlPanel_restartButton_height / 2
		);

	shapes_button_restart_border.setSize(sf::Vector2f(
		config::controlPanel_restartButtonBorder_width,
		config::controlPanel_restartButtonBorder_height
	));
	shapes_button_restart_border.setPosition(
		shapes_button_restart_upperLeft_X,
		shapes_button_restart_upperLeft_Y
	);

	shapes_status_bar.setSize(sf::Vector2f(3,
		config::controlPanel_restartButtonBorder_height + 10
	));
	shapes_status_bar.setFillColor(assets::color_grey_dark);
	shapes_status_bar.setPosition(
		config::window_width_easy * 3 / 4 - 40,
		shapes_button_restart_upperLeft_Y
	);

	shapes_status_bar_border.setSize(sf::Vector2f(3 + 4,
		config::controlPanel_restartButtonBorder_height + 10 + 4
	));
	shapes_status_bar_border.setFillColor(assets::color_grey_light);
	shapes_status_bar_border.setPosition(
		config::window_width_easy * 3 / 4 - 40 - 2,
		shapes_button_restart_upperLeft_Y - 2
	);

	shapes_records_background_overlay.setSize(sf::Vector2f(
		config::window_width_easy, config::window_height_easy
	));
	shapes_records_background_overlay.setFillColor(assets::color_grey_medium_semitransparent);
	shapes_records_background_overlay.setPosition(0,0);

	shapes_records_background_box.setSize(sf::Vector2f(
		config::window_width_easy - 100, config::window_height_easy - 10
	));
	shapes_records_background_box.setFillColor(assets::color_grey_dark);
	shapes_records_background_box.setPosition(
		config::window_width_easy / 2 - ((config::window_width_easy - 100) / 2),
		config::window_height_easy / 2 - ((config::window_height_easy - 10) / 2)
	);

	shapes_records_background_box_border.setSize(sf::Vector2f(
		config::window_width_easy - 80, config::window_height_easy - 60
	));
	shapes_records_background_box_border.setFillColor(assets::color_grey_medium_dark);
	shapes_records_background_box_border.setPosition(
		config::window_width_easy / 2 - ((config::window_width_easy - 80) / 2),
		config::window_height_easy / 2 - ((config::window_height_easy - 60) / 2)
	);



	if (!font.loadFromFile("segoeui.ttf"))
	{
		// error...
	}
	cellNumber.setFont(font);
	cellNumber.setString("1");
	cellNumber.setCharacterSize(config::pixelCharSize); // in pixels, not points!
	cellNumber.setFillColor(assets::color_grey_darkest);

	questionMark.setFont(font);
	questionMark.setString("?");
	questionMark.setCharacterSize(config::pixelCharSize); // in pixels, not points!
	questionMark.setFillColor(assets::color_grey_lightest);
	questionMark.setStyle(sf::Text::Bold);

	restartButton.setFont(font);
	restartButton.setString("Restart");
	restartButton.setCharacterSize(config::pixelCharSize); // in pixels, not points!
	restartButton.setPosition(
		config::window_width_easy / 2 - config::controlPanel_restartButtonBorder_width / 2
			+ config::controlPanel_restartButtonBorder_width * 0.17,
		config::controlPanel_height / 2 - config::controlPanel_restartButtonBorder_height / 2
			+ config::controlPanel_restartButtonBorder_height * 0.2
	);
	//restartButton.setStyle(sf::Text::Bold);

	clickCounter.setFont(font);
	clickCounter.setString("  ");
	clickCounter.setCharacterSize(config::pixelCharSize_small); // in pixels, not points!
	clickCounter.setPosition(
		config::window_width_easy * 3 / 4,
		config::controlPanel_height / 4
	);

	timerCount = clickCounter;
	timerCount.setPosition(
		config::window_width_easy * 3 / 4,
		config::controlPanel_height / 4 * 2 + 12
	);

	assets::restartButton_notHovered();

}

void assets::restartButton_hovered()
{
	shapes_button_restart.setFillColor(assets::color_grey_medium);
	shapes_button_restart_border.setFillColor(assets::color_grey_light);
	restartButton.setFillColor(assets::color_grey_lightest);
	restartButton.setString("Restart");
	/*restartButton.setPosition(
		config::window_width_easy / 2 - config::controlPanel_restartButtonBorder_width / 2
		+ config::controlPanel_restartButtonBorder_width * 0.17,
		config::controlPanel_height / 2 - config::controlPanel_restartButtonBorder_height / 2
		+ config::controlPanel_restartButtonBorder_height * 0.2
	);*/
}

void assets::restartButton_notHovered()
{
	shapes_button_restart.setFillColor(assets::color_grey_light);
	shapes_button_restart_border.setFillColor(assets::color_grey_dark);
	restartButton.setFillColor(assets::color_grey_dark);
	restartButton.setString("Restart");
	/*restartButton.setPosition(
		config::window_width_easy / 2 - config::controlPanel_restartButtonBorder_width / 2
		+ config::controlPanel_restartButtonBorder_width * 0.17,
		config::controlPanel_height / 2 - config::controlPanel_restartButtonBorder_height / 2
		+ config::controlPanel_restartButtonBorder_height * 0.2
	);*/
}

void assets::restartButton_gameWon()
{
	shapes_button_restart.setFillColor(assets::color_green_medium);
	shapes_button_restart_border.setFillColor(assets::color_grey_light);
	restartButton.setFillColor(assets::color_grey_lightest);
	restartButton.setString("Victory");
	/*restartButton.setPosition(
		config::window_width_easy / 2 - config::controlPanel_restartButtonBorder_width / 2
		+ config::controlPanel_restartButtonBorder_width * 0.09,
		config::controlPanel_height / 2 - config::controlPanel_restartButtonBorder_height / 2
		+ config::controlPanel_restartButtonBorder_height * 0.2
	);*/
}

void assets::restartButton_gameLost()
{
	shapes_button_restart.setFillColor(assets::color_red);
	shapes_button_restart_border.setFillColor(assets::color_grey_light);
	restartButton.setFillColor(assets::color_grey_lightest);
	restartButton.setString("Defeat");
	/*restartButton.setPosition(
		config::window_width_easy / 2 - config::controlPanel_restartButtonBorder_width / 2
		+ config::controlPanel_restartButtonBorder_width * 0.13,
		config::controlPanel_height / 2 - config::controlPanel_restartButtonBorder_height / 2
		+ config::controlPanel_restartButtonBorder_height * 0.2
	);*/
}

void assets::statusBar_playing()
{
	shapes_status_bar.setFillColor(assets::color_grey_lightest);
	shapes_status_bar_border.setFillColor(assets::color_grey_light);
}

void assets::statusBar_gameWon()
{
	shapes_status_bar.setFillColor(assets::color_green_medium);
	//shapes_status_bar_border.setFillColor(assets::color_green_medium);
}

void assets::statusBar_gameLost()
{
	shapes_status_bar.setFillColor(assets::color_red);
	//shapes_status_bar_border.setFillColor(assets::color_red);
}

void assets::statusBar_notPlaying()
{
	shapes_status_bar.setFillColor(assets::color_grey_light);
	//shapes_status_bar_border.setFillColor(assets::color_grey_light);
}

void assets::clickCounter_update(unsigned int count)
{
	std::string str = "    ";
	str.append(std::to_string(count));
	clickCounter.setString(str);
}

void assets::timer_update(std::string timePlayed)
{
	std::string str = "    ";
	str.append(timePlayed);
	timerCount.setString(str);
}

void assets::updatePositions(unsigned int newGameMode)
{
	auto window_width = config::window_width_easy;
	auto window_height = config::window_height_easy;
	switch (newGameMode)
	{
	case 0: // Easy
		//do nothing
		break;
	case 1: // Medium
		window_width = config::window_width_medium;
		window_height = config::window_height_medium;
		break;
	case 2: // Hard
		window_width = config::window_width_hard;
		window_height = config::window_height_hard;
		break;
	default:
		break;
	}

	shapes_pointer_arrow.setPosition(
		window_width * 3 / 4 - 15,
		config::controlPanel_height / 4 - 3
	);
	shapes_pointer_arrowTail.setPosition(
		window_width * 3 / 4 - 12,
		config::controlPanel_height / 4 + 9
	);
	shapes_stopclock_border.setPosition(
		window_width * 3 / 4 - 20,
		config::controlPanel_height / 4 * 2 + 12
	);
	shapes_stopclock_body.setPosition(
		window_width * 3 / 4 - 17,
		config::controlPanel_height / 4 * 2 + 15
	);
	shapes_stopclock_top_1.setPosition(
		window_width * 3 / 4 - 9,
		config::controlPanel_height / 4 * 2 + 8
	);
	shapes_stopclock_top_2.setPosition(
		window_width * 3 / 4 - 12,
		config::controlPanel_height / 4 * 2 + 6
	);
	shapes_stopclock_needle.setPosition(
		window_width * 3 / 4 - 7,
		config::controlPanel_height / 4 * 2 + 21
	);
	
	shapes_button_restart_upperLeft_X =
		window_width / 2 - config::controlPanel_restartButtonBorder_width / 2 - 4;
	shapes_button_restart_lowerRight_X =
		shapes_button_restart_upperLeft_X + config::controlPanel_restartButtonBorder_width;

	shapes_button_restart.setPosition(
		window_width / 2 - config::controlPanel_restartButtonBorder_width / 2,
		config::controlPanel_height / 2 - config::controlPanel_restartButton_height / 2
	);

	shapes_button_restart_border.setPosition(
		shapes_button_restart_upperLeft_X,
		shapes_button_restart_upperLeft_Y
	);

	shapes_status_bar.setPosition(
		window_width * 3 / 4 - 40,
		shapes_button_restart_upperLeft_Y
	);
	shapes_status_bar_border.setPosition(
		window_width * 3 / 4 - 40 - 2,
		shapes_button_restart_upperLeft_Y - 2
	);
	restartButton.setPosition(
		window_width / 2 - config::controlPanel_restartButtonBorder_width / 2
		+ config::controlPanel_restartButtonBorder_width * 0.17,
		config::controlPanel_height / 2 - config::controlPanel_restartButtonBorder_height / 2
		+ config::controlPanel_restartButtonBorder_height * 0.2
	);
	clickCounter.setPosition(
		window_width * 3 / 4,
		config::controlPanel_height / 4
	);
	timerCount.setPosition(
		window_width * 3 / 4,
		config::controlPanel_height / 4 * 2 + 12
	);

	shapes_records_background_overlay.setSize(sf::Vector2f(
		window_width, window_height
	));

	//shapes_records_background_box.setSize(sf::Vector2f(
	//	window_width - 200, window_height - 100
	//));
	shapes_records_background_box.setPosition(
		window_width / 2 - ((config::window_width_easy - 100) / 2),
		window_height / 2 - ((config::window_height_easy - 10) / 2)
	);

	shapes_records_background_box_border.setPosition(
		window_width / 2 - ((config::window_width_easy - 80) / 2),
		window_height / 2 - ((config::window_height_easy - 60) / 2)
	);
}

void assets::centerText(sf::Text& floatRect,
	float X_UL, float Y_UL,
	float X_BR, float Y_BR)
{
	auto boundingRect = floatRect.getGlobalBounds();
	auto center_X = X_BR - ((X_BR - X_UL) / 2);
	auto center_Y = Y_BR - ((Y_BR - Y_UL) / 2);
	floatRect.setPosition(
		center_X - boundingRect.width / 2.0f,
		center_Y - boundingRect.height);
}