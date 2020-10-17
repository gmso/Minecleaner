#include "MinecleanerApp.h"
#include "config.cpp"
#include "assets.cpp"

MinecleanerApp::MinecleanerApp()
{
	window.create(sf::VideoMode(1, 1), " ");
	//window.create(
	//	sf::VideoMode(config::window::width, config::window::height),
	//	config::window::title);
	window.setSize(sf::Vector2u(config::window::width,config::window::height));
	window.setTitle(config::window::title);
	currentGameState = MinecleanerApp::gameState::None;
}

MinecleanerApp::~MinecleanerApp()
{
}

bool MinecleanerApp::isRunning()
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

	window.clear(assets::colors::grey_medium);
	//window.draw(shape);
	window.display();
}
