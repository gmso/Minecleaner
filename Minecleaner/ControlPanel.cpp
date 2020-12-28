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
	std::string timePlayed
)
{
	drawRestartButton(window, gameState);
	drawClickCounter(window, clicks);
	drawTimer(window, timePlayed);
	drawStatusBar(window, gameState);
	drawGameModes(window);
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

void ControlPanel::processMousePosition(int x, int y)
{
	auto mouseEasy = btnEasy.processMousePosition(x, y);
	auto mouseMedium = btnMedium.processMousePosition(x, y);
	auto mouseHard = btnHard.processMousePosition(x, y);
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


