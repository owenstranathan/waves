
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
const float ALMOST_ZERO = 0.0001; // close enough
const float SEA_LEVEL = 200.f;

int main()
{
	// wabi::Time time;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 100;
    auto videoMode = sf::VideoMode::getDesktopMode();
	SCREEN_HEIGHT = videoMode.height;
	SCREEN_WIDTH = videoMode.width;
    // sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Waves!", sf::Style::None, settings);
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Waves!", sf::Style::Default, settings);
    // window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(100);
	Graphics::init();


	// Sea sea(SEA_LEVEL);
	// std::list<Rock*> rocks;
	// Gravity gravity;
	Game game(SEA_LEVEL);
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
		window << game;		
		window.display();
    }
	Graphics::cleanUp();
    return 0;
}
