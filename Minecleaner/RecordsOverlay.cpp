#include "RecordsOverlay.h"

RecordsOverlay::RecordsOverlay()
{
	displayed = false;
	posX = config::window_width_easy / 2 - ((config::window_width_easy - 100) / 2);
	posY = config::window_height_easy / 2 - ((config::window_height_easy - 80) / 2);
	posX_BR = posX + config::window_width_easy - 100;
	posY_BR = posY + config::window_height_easy - 80;
}

RecordsOverlay::~RecordsOverlay()
{
}

void RecordsOverlay::draw(sf::RenderWindow& window)
{
	if (displayed)
	{
		window.draw(assets::shapes_records_background_overlay);
		//window.draw(assets::shapes_records_background_box_border);
		window.draw(assets::shapes_records_background_box);
	
		btnClose.draw(window);
	}
}

void RecordsOverlay::processMousePosition(int x, int y)
{
	auto mouseClose = btnClose.processMousePosition(x, y);

}

bool RecordsOverlay::processLeftClick(int x, int y)
{
	auto clickClose = btnClose.processLeftClick(x, y);
	if (clickClose == Button::State::Clicked)
	{
		btnClose.deactivate(); //so button is deactivated after re-opening records overlay
	}
	return (clickClose == Button::State::Clicked);
}

void RecordsOverlay::display()
{
	displayed = true;
}

void RecordsOverlay::hide()
{
	displayed = false;
}

bool RecordsOverlay::isDisplayed()
{
	return displayed;
}

void RecordsOverlay::updatePosition(unsigned int newGameMode)
{
	auto window_width = config::window_width_easy;
	auto window_height = config::window_height_easy;
	switch (newGameMode)
	{
	case 0: // Easy
		//do nothing
		break;
	case 1: // Medium
		window_width = config::window_width_medium;
		window_height = config::window_height_medium;
		break;
	case 2: // Hard
		window_width = config::window_width_hard;
		window_height = config::window_height_hard;
		break;
	default:
		break;
	}

	posX = window_width / 2 - ((window_width - 100) / 2);
	posY = window_height / 2 - ((window_height - 80) / 2);
	posX_BR = posX + window_width - 100;
	posY_BR = posY + window_height - 80;

	btnClose.setPositionX(window_width / 2 + ((config::window_width_easy - 100) / 2) - 45);
	btnClose.setPositionY(window_height / 2 - ((config::window_height_easy - 80) / 2) + 10);
}
