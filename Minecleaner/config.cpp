#include "config.h"
#include <SFML/Graphics.hpp>

sf::String config::version_mayor = "0";
sf::String config::version_minor = "3";
sf::String config::version_bugfix = "0";
std::string config::appName = "Minecleaner by gmso";

unsigned int config::controlPanel_height = 100;
//unsigned int config::controlPanel_width = 0;

unsigned int config::game_cellsHorizontal_easy = 12;
unsigned int config::game_cellsVertical_easy = 8;
unsigned int config::game_cellsHorizontal_medium = 15;
unsigned int config::game_cellsVertical_medium = 10;
unsigned int config::game_cellsHorizontal_hard = 20;
unsigned int config::game_cellsVertical_hard = 15;
float config::game_cellSizeSide = 40;
//float config::game_marginSize = 15;
unsigned int config::game_totalCells_easy = 
	game_cellsHorizontal_easy * game_cellsVertical_easy;
unsigned int config::game_totalCells_medium = 
	game_cellsHorizontal_medium * game_cellsVertical_medium;
unsigned int config::game_totalCells_hard = 
	game_cellsHorizontal_hard * game_cellsVertical_hard;
float config::game_paddingCell= 2;
int config::game_offsetBoard_x = 0;
int config::game_offsetBoard_y = controlPanel_height;
//unsigned int config::game_bombsMinimum = game_totalCells / 10; //10% of cells are bombs
//unsigned int config::game_bombsMaximum = game_totalCells / 5; //20% of cells are bombs
unsigned int config::game_bombs_easy = 15;
unsigned int config::game_bombs_medium= 30;
unsigned int config::game_bombs_hard= 80;

unsigned int config::window_height_easy =
	config::game_cellsVertical_easy * config::game_cellSizeSide +
	config::controlPanel_height;
unsigned int config::window_width_easy =	config::game_cellsHorizontal_easy * config::game_cellSizeSide;
unsigned int config::window_height_medium =
	config::game_cellsVertical_medium * config::game_cellSizeSide +
	config::controlPanel_height;
unsigned int config::window_width_medium = config::game_cellsHorizontal_medium * config::game_cellSizeSide;
unsigned int config::window_height_hard =
	config::game_cellsVertical_hard * config::game_cellSizeSide +
	config::controlPanel_height;
unsigned int config::window_width_hard = config::game_cellsHorizontal_hard * config::game_cellSizeSide;

sf::String config::window_title = sf::String(
	appName + "   (build " + version_mayor + "." + version_minor + "." + version_bugfix + ")");

unsigned int config::pixelCharSize = 24;
unsigned int config::pixelCharSize_small = 20;
unsigned int config::pixelCharSize_smaller = 14;

unsigned int config::controlPanel_restartButton_width = config::pixelCharSize * 5;
unsigned int config::controlPanel_restartButton_height = config::pixelCharSize * 2;
unsigned int config::controlPanel_restartButtonBorder_width = 
	config::controlPanel_restartButton_width + 8;
unsigned int config::controlPanel_restartButtonBorder_height =
	config::controlPanel_restartButton_height + 8;



config::config() 
{
}
