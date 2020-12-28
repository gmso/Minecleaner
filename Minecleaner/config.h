#pragma once

#include <SFML/Graphics.hpp>

struct config
{
	config();

	static sf::String version_mayor;
	static sf::String version_minor;
	static sf::String version_bugfix;
	static std::string appName;

	static unsigned int controlPanel_height;
	//static unsigned int controlPanel_width;

	static unsigned int game_cellsHorizontal_easy;
	static unsigned int game_cellsVertical_easy;
	static unsigned int game_cellsHorizontal_medium;
	static unsigned int game_cellsVertical_medium;
	static unsigned int game_cellsHorizontal_hard;
	static unsigned int game_cellsVertical_hard;
	static float game_cellSizeSide;
	//static float game_marginSize;
	static unsigned int game_totalCells_easy;
	static unsigned int game_totalCells_medium;
	static unsigned int game_totalCells_hard;
	static float game_paddingCell;
	static int game_offsetBoard_x;
	static int game_offsetBoard_y;
	//static unsigned int game_bombsMinimum;
	//static unsigned int game_bombsMaximum;
	static unsigned int game_bombs_easy;
	static unsigned int game_bombs_medium;
	static unsigned int game_bombs_hard;

	static unsigned int window_height_easy;
	static unsigned int window_width_easy;
	static unsigned int window_height_medium;
	static unsigned int window_width_medium;
	static unsigned int window_height_hard;
	static unsigned int window_width_hard;
	static sf::String window_title;

	static unsigned int pixelCharSize;
	static unsigned int pixelCharSize_small;
	static unsigned int pixelCharSize_smaller;

	static unsigned int controlPanel_restartButton_width;
	static unsigned int controlPanel_restartButton_height;
	static unsigned int controlPanel_restartButtonBorder_width;
	static unsigned int controlPanel_restartButtonBorder_height;

};

/*
namespace config
{
	namespace game
	{
		extern unsigned int cellsHorizontal = 20;
		unsigned int cellsVertical = 10;
		unsigned int cellSizeSide = 40;
		unsigned int marginSize = 15;
		unsigned int totalCells = cellsHorizontal * cellsVertical;
		unsigned int bombsMinimum = totalCells / 10; //10% of cells are bombs
		unsigned int bombsMaximum = totalCells / 5; //20% of cells are bombs
	}
	namespace window
	{
		unsigned int height =
			config::game::cellsVertical * config::game::cellSizeSide +
			2 * (config::game::marginSize);
		unsigned int width =
			config::game::cellsHorizontal * config::game::cellSizeSide +
			2 * (config::game::marginSize);
		const sf::String title = "Minecleaner by gmso";
	}
	namespace shapes
	{
		sf::RectangleShape cell;

		//	(config::game::cellSizeSide).f,
		//	(config::game::cellsHorizontal).f));
	}
}
*/