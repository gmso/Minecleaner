///////////////////////////////
// Library headers ////////////
///////////////////////////////
#include <SFML/Graphics.hpp>

///////////////////////////////
// Project headers ////////////
///////////////////////////////
#include "MinecleanerApp.h"
#include "assets.h"
#include "config.h"

///////////////////////////////
// Main routine ///////////////
///////////////////////////////
int main()
{
    assets::intialize();
    MinecleanerApp app;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode(config::window_width, config::window_height), 
        config::window_title,
        sf::Style::Titlebar | sf::Style::Close,
        settings);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    app.processLeftClick(event.mouseButton.x, event.mouseButton.y);
                }
                else if (event.mouseButton.button == sf::Mouse::Right)
                {
                    app.processRightClick(event.mouseButton.x, event.mouseButton.y);
                }
            }
            if (event.type == sf::Event::MouseMoved)
            {
                app.processMousePosition(event.mouseMove.x, event.mouseMove.y);
            }
        }

        window.clear(assets::color_grey_medium);
        app.draw(window);
        window.display();
    }
    
    return 0;
}