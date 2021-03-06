#include "ControlPanel.h"

ControlPanel::ControlPanel()
{
	restartButton_hovered = false;
	restartButton_overrideUnhovered = false;
	difficulty = ControlPanel::gameDifficulty::Easy;
	btnEasy.activate();
}

ControlPanel::~ControlPanel()
{
}

void ControlPanel::draw(
	sf::RenderWindow& window, 
	unsigned int gameState, 
	unsigned int clicks,
	std::string timePlayed,
	unsigned int livesRemaining
)
{
	drawRestartButton(window, gameState);
	drawClickCounter(window, clicks);
	drawTimer(window, timePlayed);
	drawStatusBar(window, gameState);
	drawGameModes(window);
	drawLivesRemaining(window, livesRemaining);
	drawButtonRecords(window);
}

ControlPanel::gameDifficulty ControlPanel::getDifficulty()
{
	return difficulty;
}

ControlPanel::gameDifficulty ControlPanel::processLeftClick(int x, int y)
{
	auto clickEasy = btnEasy.processLeftClick(x, y);
	auto clickMedium = btnMedium.processLeftClick(x, y);
	auto clickHard = btnHard.processLeftClick(x, y);
	toggleGameMode(clickEasy, clickMedium, clickHard);

	switch (difficulty)
	{
	case ControlPanel::gameDifficulty::Easy:
		btnMedium.deactivate();
		btnHard.deactivate();
		break;
	case ControlPanel::gameDifficulty::Medium:
		btnEasy.deactivate();
		btnHard.deactivate();
		break;
	case ControlPanel::gameDifficulty::Hard:
		btnEasy.deactivate();
		btnMedium.deactivate();
		break;
	default:
		break;
	}

	return difficulty;
}

bool ControlPanel::processRecordsClick(int x, int y)
{
	auto clickRecords = btnRecords.processLeftClick(x, y);
	if (clickRecords == Button::State::Clicked)
	{
		btnRecords.deactivate(); //so button is deactivated after closing records overlay
	}
	return (clickRecords == Button::State::Clicked);
}

void ControlPanel::processMousePosition(int x, int y)
{
	auto mouseEasy = btnEasy.processMousePosition(x, y);
	auto mouseMedium = btnMedium.processMousePosition(x, y);
	auto mouseHard = btnHard.processMousePosition(x, y);
	auto mouseRecords = btnRecords.processMousePosition(x, y);
	//toggleGameMode(mouseEasy, mouseMedium, mouseHard);

	if (assets::shapes_button_restart_upperLeft_X <= x &&
		x <= assets::shapes_button_restart_lowerRight_X &&
		assets::shapes_button_restart_upperLeft_Y <= y &&
		y <= assets::shapes_button_restart_lowerRight_Y)
	{
		//Restart button hovered
		restartButton_hovered = true;
		assets::restartButton_hovered();
	}
	else
	{
		restartButton_hovered = false;
		if (!(restartButton_overrideUnhovered))
		{
			assets::restartButton_notHovered();
		}
	}
}

void ControlPanel::drawRestartButton(sf::RenderWindow& window, unsigned int gameState)
{
	window.draw(assets::shapes_button_restart_border);
	window.draw(assets::shapes_button_restart);

	switch (gameState)
	{
	case 2: // Lost
		if (!(restartButton_hovered))
		{
			restartButton_overrideUnhovered = true;
			assets::restartButton_gameLost();
		}
		break;
	case 3: // Won
		if (!(restartButton_hovered))
		{
			restartButton_overrideUnhovered = true;
			assets::restartButton_gameWon();
		}
		break;
	default:
		if (restartButton_overrideUnhovered)
		{
			assets::restartButton_hovered();
		}
		restartButton_overrideUnhovered = false;
		break;
	}
	window.draw(assets::restartButton);
}

void ControlPanel::drawClickCounter(sf::RenderWindow& window, unsigned int clicks)
{
	assets::clickCounter_update(clicks);
	window.draw(assets::clickCounter);
	window.draw(assets::shapes_pointer_arrow);
	window.draw(assets::shapes_pointer_arrowTail);
}

void ControlPanel::drawTimer(sf::RenderWindow& window, std::string timePlayed)
{
	window.draw(assets::shapes_stopclock_border);
	window.draw(assets::shapes_stopclock_top_1);
	window.draw(assets::shapes_stopclock_top_2);
	window.draw(assets::shapes_stopclock_body);
	window.draw(assets::shapes_stopclock_needle);
	assets::timer_update(timePlayed);
	window.draw(assets::timerCount);
}

void ControlPanel::drawStatusBar(sf::RenderWindow& window, unsigned int gameState)
{
	switch (gameState)
	{
	case 1: // Playing
		assets::statusBar_playing();
		window.draw(assets::shapes_status_bar_border);
		break;
	case 2: // Lost
		assets::statusBar_gameLost();
		window.draw(assets::shapes_status_bar_border);
		break;
	case 3: // Won
		assets::statusBar_gameWon();
		window.draw(assets::shapes_status_bar_border);
		break;
	default:
		assets::statusBar_notPlaying();
		break;
	}
	window.draw(assets::shapes_status_bar);
}

void ControlPanel::drawGameModes(sf::RenderWindow& window)
{
	btnEasy.draw(window);
	btnMedium.draw(window);
	btnHard.draw(window);
}

void ControlPanel::drawLivesRemaining(sf::RenderWindow& window, unsigned int livesRemaining)
{
	sf::RectangleShape pole = assets::shapes_flag_pole;
	sf::CircleShape flag = assets::shapes_flag_flag;
	sf::CircleShape flagBorder = assets::shapes_flag_flagBorder;

	flag.setFillColor(assets::color_yellow);

	for (size_t i = 0; i < livesRemaining; i++)
	{
		pole.setPosition(
			config::controlPanel_height / 20 * 4 + 20 * i + config::game_cellSizeSide * 0.42,
			60 + config::game_cellSizeSide * 0.2
		);
		flag.setPosition(
			config::controlPanel_height / 20 * 4 + 20 * i + config::game_cellSizeSide * 0.18,
			60 + config::game_cellSizeSide * 0.5
		);
		flagBorder.setPosition(
			config::controlPanel_height / 20 * 4 + 20 * i + config::game_cellSizeSide * 0.1,
			60 + config::game_cellSizeSide * 0.57
		);
		window.draw(pole);
		window.draw(flagBorder);
		window.draw(flag);
	}
}

void ControlPanel::drawButtonRecords(sf::RenderWindow& window)
{
	btnRecords.draw(window);
}

ControlPanel::gameDifficulty ControlPanel::toggleGameMode(
	Button::State Easy, Button::State Medium, Button::State Hard)
{
	switch (difficulty)
	{
	case ControlPanel::gameDifficulty::Easy:
		if (Medium == Button::State::Clicked)
		{
			difficulty = gameDifficulty::Medium;
		}
		else if (Hard == Button::State::Clicked)
		{
			difficulty = gameDifficulty::Hard;
		}
		break;
	case ControlPanel::gameDifficulty::Medium:
		if (Easy == Button::State::Clicked)
		{
			difficulty = gameDifficulty::Easy;
		}
		else if (Hard == Button::State::Clicked)
		{
			difficulty = gameDifficulty::Hard;
		}
		break;
	case ControlPanel::gameDifficulty::Hard:
		if (Easy == Button::State::Clicked)
		{
			difficulty = gameDifficulty::Easy;
		}
		else if (Medium == Button::State::Clicked)
		{
			difficulty = gameDifficulty::Medium;
		}
		break;
	default:
		break;
	}
	return difficulty;
}

void ControlPanel::updatePositions(unsigned int newGameMode)
{
	auto window_width = config::window_width_easy;
	switch (newGameMode)
	{
	case 0: // Easy
		//do nothing
		break;
	case 1: // Medium
		window_width = config::window_width_medium;
		break;
	case 2: // Hard
		window_width = config::window_width_hard;
		break;
	default:
		break;
	}

	btnRecords.setPositionX(window_width - 50);
}


