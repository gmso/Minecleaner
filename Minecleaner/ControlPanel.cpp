#include "ControlPanel.h"

ControlPanel::ControlPanel()
{
	restartButton_hovered = false;
}

ControlPanel::~ControlPanel()
{
}

void ControlPanel::draw(sf::RenderWindow& window)
{
	drawRestartButton(window);
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
		assets::restartButton_notHovered();
	}
}

void ControlPanel::drawRestartButton(sf::RenderWindow& window)
{
	window.draw(assets::shapes_button_restart_border);
	window.draw(assets::shapes_button_restart);
	window.draw(assets::restartButton);
}

