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
          
    sf::RenderWindow window(
        sf::VideoMode(config::window_width, config::window_height), 
        config::window_title);
    //sf::CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(assets::color_grey_medium);
        app.draw(window);
        //window.draw(shape);
        window.display();
    }
    
    return 0;
}