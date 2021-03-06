
#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <SFML/Graphics.hpp>

#include "prelude.hpp"
#include "utils.hpp"
#include "game.hpp"
#include "graphics.hpp"
#include "gravity.hpp"
#include "sea.hpp"
#include "rock.hpp"

int SCREEN_MULT = 100;
int SCREEN_HEIGHT = 9 * SCREEN_MULT;
int SCREEN_WIDTH = 16 * SCREEN_MULT;
const float ALMOST_ZERO = 0.01; // close enough
// const float SEA_LEVEL = 200.f;
const float SEA_LEVEL = 13.3f;

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 100;
    auto videoMode = sf::VideoMode::getDesktopMode();
    // SCREEN_HEIGHT = videoMode.height;
    // SCREEN_WIDTH = videoMode.width;
    // std::cout << SCREEN_HEIGHT << " " << SCREEN_WIDTH << std::endl;
    // sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Waves!", sf::Style::None, settings);
    sf::RenderWindow window(videoMode, "Waves!", sf::Style::Default, settings);
    window.setFramerateLimit(100);
    window.setVerticalSyncEnabled(true);

    Game game(SEA_LEVEL);
    Graphics graphics(&game, &window, videoMode);
    // game loop
    while (!game.over && window.isOpen())
    {
        game.update();
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            game.handleEvent(event);
        }
        graphics.draw();
        window.display();
    }
    return 0;
}
