///////////////////////////////
// Library headers ////////////
///////////////////////////////
#include <SFML/Graphics.hpp>

///////////////////////////////
// Project headers ////////////
///////////////////////////////

///////////////////////////////
// Main routine ///////////////
///////////////////////////////
int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "Minecleaner by gmso");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}