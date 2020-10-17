#include <SFML\System.hpp>

namespace config
{
	namespace game
	{
		constexpr unsigned int cellsHorizontal = 20;
		constexpr unsigned int cellsVertical = 10;
		constexpr unsigned int cellSizeSide = 40;
		constexpr unsigned int marginSize = 15;
		constexpr unsigned int totalCells = cellsHorizontal * cellsVertical;
		constexpr unsigned int bombsMinimum = totalCells / 10; //10% of cells are bombs
		constexpr unsigned int bombsMaximum = totalCells / 5; //20% of cells are bombs
	}
	namespace window
	{
		constexpr unsigned int height =
			config::game::cellsVertical * config::game::cellSizeSide + 
			2 * (config::game::marginSize);
		constexpr unsigned int width =
			config::game::cellsHorizontal * config::game::cellSizeSide +
			2*(config::game::marginSize);
		const sf::String title = "Minecleaner by gmso";
	}
}