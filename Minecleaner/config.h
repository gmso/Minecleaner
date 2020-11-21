#pragma once

#include <SFML/Graphics.hpp>

struct config
{
	config();

	static unsigned int controlPanel_height;
	//static unsigned int controlPanel_width;

	static unsigned int game_cellsHorizontal;
	static unsigned int game_cellsVertical;
	static float game_cellSizeSide;
	//static float game_marginSize;
	static unsigned int game_totalCells;
	static float game_paddingCell;
	static int game_offsetBoard_x;
	static int game_offsetBoard_y;
	static unsigned int game_bombsMinimum;
	static unsigned int game_bombsMaximum;

	static unsigned int window_height;
	static unsigned int window_width;
	static sf::String window_title;

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