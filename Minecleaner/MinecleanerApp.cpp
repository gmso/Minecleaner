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
	currentGameState = MinecleanerApp::gameState::None;
	timerRunning = false;
	currentDificulty = panel.getDifficulty();
	board.reset(static_cast<unsigned int>(currentDificulty));
}

MinecleanerApp::~MinecleanerApp()
{
}

void MinecleanerApp::draw(sf::RenderWindow& window)
{
	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Green);
	//window.draw(shape);
	panel.draw(
		window, 
		static_cast<unsigned int>(currentGameState),
		board.getValidClicks(),
		getTimer()
		);
	board.draw(
		window, 
		currentGameState == MinecleanerApp::gameState::Lost,
		currentGameState == MinecleanerApp::gameState::Won);
}

void MinecleanerApp::processLeftClick(int x, int y, sf::RenderWindow& window)
{
	if (boardClickingAllowed())
	{
		if (x >= config::game_offsetBoard_x && 
			y >= config::game_offsetBoard_y)
		{
			switch (board.processLeftClick(
				x - config::game_offsetBoard_x,
				y - config::game_offsetBoard_y))
			{
			case MinecleanerBoard::leftClickResult::Mine:
				updateGameState(MinecleanerApp::gameState::Lost);
				break;
			case MinecleanerBoard::leftClickResult::CellsCleared:
				updateGameState(MinecleanerApp::gameState::Won);
				break;
			default:
				updateGameState(MinecleanerApp::gameState::Playing);
				break;
			}
		}
	}

	bool changeDifficulty = false;
	auto newDifficulty = panel.processLeftClick(x, y);
	if (newDifficulty != currentDificulty)
	{
		changeDifficulty = true;
		currentDificulty = newDifficulty;
		resizeWindow(window, newDifficulty);
	}

	if ((assets::shapes_button_restart_upperLeft_X <= x &&
		x <= assets::shapes_button_restart_lowerRight_X &&
		assets::shapes_button_restart_upperLeft_Y <= y &&
		y <= assets::shapes_button_restart_lowerRight_Y)
		||
		changeDifficulty)
	{
		//Restart button clicked
		updateGameState(MinecleanerApp::gameState::Restarting);
		board.reset(static_cast<unsigned int>(currentDificulty));
		assets::updatePositions(static_cast<unsigned int>(currentDificulty));
		updateGameState(MinecleanerApp::gameState::None);
	}
}

void MinecleanerApp::processRightClick(int x, int y)
{
	if (boardClickingAllowed())
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
	if (boardClickingAllowed())
	{
		board.processMousePosition(x, y);
	}
}

void MinecleanerApp::updateGameState(gameState newState)
{
	if (currentGameState == MinecleanerApp::gameState::None &&
		newState == MinecleanerApp::gameState::Playing)
	{
		startTimer();
	}
	else if (currentGameState == MinecleanerApp::gameState::None &&
		newState != MinecleanerApp::gameState::Playing)
	{
		startTimer();
		stopTimer();
	}
	else if (currentGameState == MinecleanerApp::gameState::Playing &&
		newState != MinecleanerApp::gameState::Playing)
	{
		stopTimer();
	}

	currentGameState = newState;
}

bool MinecleanerApp::boardClickingAllowed()
{
	return (
		currentGameState == MinecleanerApp::gameState::None ||
		currentGameState == MinecleanerApp::gameState::Playing
		);
}

void MinecleanerApp::resizeWindow(
	sf::RenderWindow& win, 
	ControlPanel::gameDifficulty newDiff)
{
	sf::FloatRect visibleAreaEasy(0, 0, config::window_width_easy, config::window_height_easy);
	sf::FloatRect visibleAreaMed(0, 0, config::window_width_medium, config::window_height_medium);
	sf::FloatRect visibleAreaHard(0, 0, config::window_width_hard, config::window_height_hard);

	switch (newDiff)
	{
	case ControlPanel::gameDifficulty::Easy:
		win.setSize(sf::Vector2u(config::window_width_easy, config::window_height_easy));
		win.setView(sf::View(visibleAreaEasy));
		break;
	case ControlPanel::gameDifficulty::Medium:
		win.setSize(sf::Vector2u(config::window_width_medium, config::window_height_medium));
		win.setView(sf::View(visibleAreaMed));
		break;
	case ControlPanel::gameDifficulty::Hard:
		win.setSize(sf::Vector2u(config::window_width_hard, config::window_height_hard));
		win.setView(sf::View(visibleAreaHard));
		break;
	default:
		break;
	}
}

void MinecleanerApp::startTimer()
{
	timerRunning = true;
	timerStart = std::chrono::steady_clock::now();
	timerEnd = timerStart;
}

void MinecleanerApp::stopTimer()
{
	timerRunning = false;
	timerEnd = std::chrono::steady_clock::now();
}

std::string MinecleanerApp::getTimer()
{
	if (timerRunning)
	{
		timerEnd = std::chrono::steady_clock::now();
	}
	std::chrono::duration<double> seconds = timerEnd - timerStart;

	unsigned int int_seconds = static_cast<unsigned int>(seconds.count());

	unsigned int int_minutes = int_seconds / 60;
	std::string str_minutes = std::to_string(int_minutes);

	int_seconds = int_seconds - int_minutes * 60;
	std::string str_seconds= std::to_string(int_seconds);

	unsigned int int_ms = static_cast<unsigned int>
		((seconds.count() - static_cast<double>(int_seconds) - static_cast<double>(int_minutes * 60))
			* 10) ;
	std::string str_ms = std::to_string(int_ms);

	std::string time = "";
	if (int_minutes > 0)
	{
		time.append(str_minutes + " : ");
	}
	time.append(str_seconds);
	//if (!timerRunning)
	//{
		time.append(" ' " + str_ms);
	//}

	if (currentGameState == MinecleanerApp::gameState::None)
	{
		return "0";
	}
	return time;
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