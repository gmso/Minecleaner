#include "ControlPanel.h"

ControlPanel::ControlPanel()
{
	restartButton_hovered = false;
	restartButton_overrideUnhovered = false;
}

ControlPanel::~ControlPanel()
{
}

void ControlPanel::draw(sf::RenderWindow& window, unsigned int gameState, unsigned int clicks)
{
	drawRestartButton(window, gameState);
	drawClickCounter(window,clicks);
}

int ControlPanel::processLeftClick(int x, int y)
{
	return 0;
}

void ControlPanel::processMousePosition(int x, int y)
{
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
}

