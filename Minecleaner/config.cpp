#include "config.h"
#include <SFML/Graphics.hpp>

sf::String config::version_mayor = "0";
sf::String config::version_minor = "1";
sf::String config::version_bugfix = "1";
std::string config::appName = "Minecleaner by gmso";

unsigned int config::controlPanel_height = 100;
//unsigned int config::controlPanel_width = 0;

unsigned int config::game_cellsHorizontal = 20;
unsigned int config::game_cellsVertical = 10;
float config::game_cellSizeSide = 40;
//float config::game_marginSize = 15;
unsigned int config::game_totalCells = game_cellsHorizontal * game_cellsVertical;
float config::game_paddingCell= 2;
int config::game_offsetBoard_x = 0;
int config::game_offsetBoard_y = controlPanel_height;
unsigned int config::game_bombsMinimum = game_totalCells / 10; //10% of cells are bombs
unsigned int config::game_bombsMaximum = game_totalCells / 5; //20% of cells are bombs

unsigned int config::window_height = 
	config::game_cellsVertical * config::game_cellSizeSide +
	config::controlPanel_height;
unsigned int config::window_width =	config::game_cellsHorizontal * config::game_cellSizeSide;
sf::String config::window_title = sf::String(
	appName + "   (build " + version_mayor + "." + version_minor + "." + version_bugfix + ")");

unsigned int config::pixelCharSize = 24;
unsigned int config::pixelCharSize_small = 20;

unsigned int config::controlPanel_restartButton_width = config::pixelCharSize * 5;
unsigned int config::controlPanel_restartButton_height = config::pixelCharSize * 2;
unsigned int config::controlPanel_restartButtonBorder_width = 
	config::controlPanel_restartButton_width + 8;
unsigned int config::controlPanel_restartButtonBorder_height =
	config::controlPanel_restartButton_height + 8;



config::config() 
{
}
