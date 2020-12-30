#include "Button.h"

/*Button::Button()
{
}*/

Button::Button(float X, float Y, std::string txt,
	unsigned int txtSize, sf::Color c_acc, sf::Color c_neu, sf::Color c_neu_dark)
{
	posX = X;
	posY = Y;
	textButton = txt;
	textSize = txtSize;
	color_accent = c_acc;
	color_neutral = c_neu;
	color_neutral_dark = c_neu_dark;

	currentState = State::Inactive;

	initialize_background();
	initialize_text();
	set_inactive();
}

Button::~Button()
{
}

void Button::deactivate()
{
	updateState(Button::State::Inactive);
}

void Button::activate()
{
	updateState(Button::State::Active);
}

void Button::draw(sf::RenderWindow& window)
{
	window.draw(button_border);
	window.draw(button_background);
	window.draw(button_text);
}

Button::State Button::processMousePosition(int x, int y)
{
	if (posX <= x && x <= posX_BR &&
		posY <= y && y <= posY_BR)
	{
		switch (currentState)
		{
		case Button::State::Inactive:
			updateState(Button::State::Hovered);
			break;
		case Button::State::Hovered:
			break;
		case Button::State::Clicked:
			updateState(Button::State::Active);
			break;
		case Button::State::Active:
			//updateState(Button::State::Hovered);
			break;
		default:
			break;
		}
	}
	else
	{
		switch (currentState)
		{
		case Button::State::Inactive:
			break;
		case Button::State::Hovered:
			//if (currentState != Button::State::Active)
			//{
				updateState(Button::State::Inactive);
			//}
			break;
		case Button::State::Clicked:
			updateState(Button::State::Active);
			break;
		case Button::State::Active:
			break;
		default:
			break;
		}
	}
	return currentState;
}

Button::State Button::processLeftClick(int x, int y)
{
	if (posX <= x && x <= posX_BR &&
		posY <= y && y <= posY_BR)
	{
		updateState(Button::State::Clicked);
	}
	return currentState;
}

void Button::setPositionX(int x)
{
	posX = x;
	initialize_background();
	initialize_text();
	//posX_BR = x + textSize * textButton.size() * 1.75;
	//button_border.setPosition(x, posY);
	//button_background.setPosition(x + 3, posY + 3);
	//button_text.setPosition(x + 8, posY);
}

void Button::setPositionY(int y)
{
	posY = y;
	initialize_background();
	initialize_text();
}

void Button::initialize_background()
{
	//auto maxText = std::max(
	//	{text_Inactive.size(),text_Hovered.size(), text_Clicked.size()});

	posX_BR = posX + textSize * textButton.size() * 1.75;
	posY_BR = posY + textSize * 1.75;

	button_border.setSize(sf::Vector2f(
		posX_BR - posX,
		posY_BR - posY
	));
	button_border.setPosition(posX, posY);

	button_background.setSize(sf::Vector2f(
		posX_BR - posX - 6,
		posY_BR - posY - 6
	));
	button_background.setPosition(posX + 3, posY + 3);
}

void Button::initialize_text()
{
	button_text.setFont(assets::font);
	button_text.setString(textButton);
	button_text.setCharacterSize(config::pixelCharSize); // in pixels, not points!
	button_text.setPosition(posX + 8, posY);
}

void Button::updateState(Button::State newState)
{
	currentState = newState;
	switch (newState)
	{
	case Button::State::Inactive:
		set_inactive();
		break;
	case Button::State::Hovered:
		set_hover();
		break;
	case Button::State::Clicked:
		set_clicked();
		break;
	case Button::State::Active:
		set_active();
		break;
	default:
		break;
	}
}

void Button::set_inactive()
{
	button_border.setFillColor(color_neutral_dark);
	button_background.setFillColor(color_neutral);
	button_text.setFillColor(color_neutral_dark);
}

void Button::set_hover()
{
	//button_border.setFillColor(color_neutral_dark);
	//button_background.setFillColor(color_neutral);
	button_text.setFillColor(color_accent);
}

void Button::set_clicked()
{
	button_border.setFillColor(color_accent);
	button_background.setFillColor(color_accent);
	button_text.setFillColor(color_neutral);
}

void Button::set_active()
{
	button_border.setFillColor(color_accent);
	button_background.setFillColor(color_neutral);
	button_text.setFillColor(color_accent);
}
