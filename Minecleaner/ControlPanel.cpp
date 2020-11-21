#include "ControlPanel.h"

ControlPanel::ControlPanel()
{
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

void ControlPanel::drawRestartButton(sf::RenderWindow& window)
{
	window.draw(assets::shapes_button_restart_border);
	window.draw(assets::shapes_button_restart);
	window.draw(assets::restartButton);
}

