#include "MinecleanerApp.h"
#include "config.h"
#include "assets.h"

MinecleanerApp::MinecleanerApp()
{
	//assets::intialize();

	//window.create(sf::VideoMode(1, 1), " ");
	//window.create(
	//	sf::VideoMode(config::window::width, config::window::height),
	//	config::window::title);
	//window.setSize(sf::Vector2u(config::window_width,config::window_height));
	//window.setTitle(config::window_title);
	currentGameState = MinecleanerApp::gameState::Playing/*None*/;
}

MinecleanerApp::~MinecleanerApp()
{
}

void MinecleanerApp::draw(sf::RenderWindow& window)
{
	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Green);
	//window.draw(shape);
	panel.draw(window, static_cast<unsigned int>(currentGameState));
	board.draw(
		window, 
		currentGameState == MinecleanerApp::gameState::Lost);
}

void MinecleanerApp::processLeftClick(int x, int y)
{
	if (currentGameState == MinecleanerApp::gameState::Playing)
	{
		if (x >= config::game_offsetBoard_x && 
			y >= config::game_offsetBoard_y)
		{
			switch (board.processLeftClick(
				x - config::game_offsetBoard_x,
				y - config::game_offsetBoard_y))
			{
			case MinecleanerBoard::leftClickResult::Mine:
				currentGameState = MinecleanerApp::gameState::Lost;
				break;
			case MinecleanerBoard::leftClickResult::CellsCleared:
				currentGameState = MinecleanerApp::gameState::Won;
				break;
			default:
				break;
			}
		}
	}
	if (assets::shapes_button_restart_upperLeft_X <= x &&
		x <= assets::shapes_button_restart_lowerRight_X &&
		assets::shapes_button_restart_upperLeft_Y <= y &&
		y <= assets::shapes_button_restart_lowerRight_Y)
	{
		//Restart button clicked
		currentGameState = MinecleanerApp::gameState::Restarting;
		board.reset();
		currentGameState = MinecleanerApp::gameState::Playing;
	}
}

void MinecleanerApp::processRightClick(int x, int y)
{
	if (currentGameState == MinecleanerApp::gameState::Playing)
	{
		if (x >= config::game_offsetBoard_x &&
			y >= config::game_offsetBoard_y)
		{
			board.processRightClick(
				x - config::game_offsetBoard_x,
				y - config::game_offsetBoard_y);
		}
	}
}

void MinecleanerApp::processMousePosition(int x, int y)
{
	panel.processMousePosition(x, y);
	if (currentGameState == MinecleanerApp::gameState::Playing)
	{
		board.processMousePosition(x, y);
	}
}

/*bool MinecleanerApp::isRunning()
{
	return (window.isOpen());
}

void MinecleanerApp::processEvent(sf::Event& event)
{
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}

	window.clear(assets::color_grey_medium);
	board.draw(window);
	sf::CircleShape shape(50.f);
	shape.setFillColor(sf::Color(100, 250, 50));
	window.draw(shape);
	window.display();
}
*/