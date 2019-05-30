
#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <SFML/Graphics.hpp>

#include "utils.hpp"
#include "wave.hpp"
#include "graphics.hpp"


int SCREEN_MULT = 100;
int SCREEN_HEIGHT = 9 * SCREEN_MULT;
int SCREEN_WIDTH = 16 * SCREEN_MULT;
const float ALMOST_ZERO = 0.0001; // close enough

int main()
{
	wabi::Time time;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 10;
    auto videoMode = sf::VideoMode::getDesktopMode();
	SCREEN_HEIGHT = videoMode.height;
	SCREEN_WIDTH = videoMode.width;
	sf::Text infoText;
	sf::Font font;
	font.loadFromFile("assets/fonts/IBMPlexMono-Regular.ttf");
	infoText.setFont(font);
	std::stringstream infostream;
    // sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Waves!", sf::Style::None, settings);
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Waves!", sf::Style::Default, settings);
    // window.setVerticalSyncEnabled(true);
	// window.setFramerateLimit(100);

    int frames = 0;
	float fixedTimeStep = 0.02f;
	float timeSinceLastFixedUpdate = 0.0f;
	
	Sea sea;
	sea.createWave(SCREEN_WIDTH / 2, 100);
	
	// game loop
    while (window.isOpen())
    {
		infostream.str(std::string());
		time.keepTime();
		frames++;
	    timeSinceLastFixedUpdate += time.deltaTime.count();
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::White);

		if (timeSinceLastFixedUpdate >= fixedTimeStep) {
			timeSinceLastFixedUpdate = 0.0f;
			sea.fixedUpdate();
		}

		auto avg = frames / time.totalTime.count();
		if (time.totalTime.count() > 1) {
			frames = 0;
			time.reset();
		}

        infostream << "FrameRate    : " << avg << std::endl;
		infostream << "deltaTime    : " << time.deltaTime.count() << std::endl;
		infostream << "t            : " << sea.waves.front()->t << std::endl;
		infoText.setString(infostream.str());
		infoText.setPosition(3, 3);
		infoText.setColor(sf::Color::Magenta);
		window.draw(infoText);
		// window << wave;
		window << sea;
        window.display();
    }
    return 0;
}
