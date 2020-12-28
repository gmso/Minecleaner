#pragma once

#include <SFML/Graphics.hpp>
#include "assets.h"
#include "config.h"

class Button
{
public:
	Button() = delete;
	Button(
		float X,
		float Y,
		std::string txt,
		unsigned int txtSize = config::pixelCharSize_small,
		sf::Color c_acc = assets::color_grey_lightest,
		sf::Color c_neu = assets::color_grey_light,
		sf::Color c_neu_dark = assets::color_grey_dark
	);

	~Button();

	enum class State { Inactive, Hovered, Clicked, Active};
	void deactivate();
	void activate();

	void draw(sf::RenderWindow& window);
	State processMousePosition(int x, int y);
	State processLeftClick(int x, int y);	

private:
	float posX;
	float posY;
	std::string textButton;
	unsigned int textSize;
	sf::Color color_accent;
	sf::Color color_neutral;
	sf::Color color_neutral_dark;

	float posX_BR;
	float posY_BR;

	sf::RectangleShape button_border;
	sf::RectangleShape button_background;
	sf::Text button_text;

	State currentState;

	void initialize_background();
	void initialize_text();

	void updateState(Button::State newState);
	void set_inactive();
	void set_hover();
	void set_clicked();
	void set_active();
};

