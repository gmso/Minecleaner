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
// Helper functions ///////////
///////////////////////////////
void loadIcon(sf::RenderWindow& window)
{
    auto image = sf::Image{};
    if (!image.loadFromFile("Icon.png"))
    {
        // Error handling...
    }
    else
    {
        window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    }
}

/*void resizeWindowIfNeeded(
    sf::RenderWindow& win, 
    const MinecleanerApp& app,
    ControlPanel::gameDifficulty currentDiff
)
{
    auto newDiff = app.getGameDifficulty();
    if (newDiff != currentDiff)
    {
        currentDiff = newDiff;
        switch (newDiff)
        {
        case ControlPanel::gameDifficulty::Easy:
            win.setSize(sf::Vector2u(config::window_width_easy, config::window_height_easy));
            break;
        case ControlPanel::gameDifficulty::Medium:
            win.setSize(sf::Vector2u(config::window_width_medium, config::window_height_medium));
            break;
        case ControlPanel::gameDifficulty::Hard:
            win.setSize(sf::Vector2u(config::window_width_hard, config::window_height_hard));
            break;
        default:
            break;
        }
    }
}*/

///////////////////////////////
// Main routine ///////////////
///////////////////////////////
int main()
{
    assets::intialize();
    MinecleanerApp app;
    ControlPanel::gameDifficulty currentDifficulty = ControlPanel::gameDifficulty::Easy;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode(config::window_width_easy, config::window_height_easy), 
        config::window_title,
        sf::Style::Titlebar | sf::Style::Close,
        settings);

    loadIcon(window);

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
                    app.processLeftClick(event.mouseButton.x, event.mouseButton.y, window);
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

        //resizeWindowIfNeeded(window, app, currentDifficulty);
        window.clear(assets::color_grey_medium);
        app.draw(window);
        window.display();
    }
    
    return 0;
}