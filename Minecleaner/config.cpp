#include "config.h"
#include <SFML/Graphics.hpp>

unsigned int config::game_cellsHorizontal = 20;
unsigned int config::game_cellsVertical = 10;
float config::game_cellSizeSide = 40;
//float config::game_marginSize = 15;
unsigned int config::game_totalCells = game_cellsHorizontal * game_cellsVertical;
float config::game_paddingCell= 2;
unsigned int config::game_bombsMinimum = game_totalCells / 10; //10% of cells are bombs
unsigned int config::game_bombsMaximum = game_totalCells / 5; //20% of cells are bombs

unsigned int config::window_height = config::game_cellsVertical * config::game_cellSizeSide;
unsigned int config::window_width =	config::game_cellsHorizontal * config::game_cellSizeSide;
sf::String config::window_title = "Minecleaner by gmso";

config::config() 
{
}
