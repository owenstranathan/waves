
#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <SFML/Graphics.hpp>

#include "utils.hpp"
#include "wave.hpp"
#include "graphics.hpp"
#include "rock.hpp"
#include "gravity.hpp"


int SCREEN_MULT = 100;
int SCREEN_HEIGHT = 9 * SCREEN_MULT;
int SCREEN_WIDTH = 16 * SCREEN_MULT;
const float ALMOST_ZERO = 0.0001; // close enough

void blah(Sea& sea) {
	static bool done = false;
	if (!done) {
		sea.createWave(SCREEN_WIDTH / 4, 100);
		done = true;
	}
}


int main()
{
	wabi::Time time;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 100;
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
	window.setFramerateLimit(100);

    int frames = 0;
	float fixedTimeStep = 0.02f;
	float timeSinceLastFixedUpdate = 0.0f;
	
	Sea sea;
	sea.createWave((SCREEN_WIDTH / 2) + 100, 50);
	sea.createWave(SCREEN_WIDTH / 2, 100);
	sea.createWave(SCREEN_WIDTH / 4, 100);
	sea.createWave(3* SCREEN_WIDTH / 4, 100);
	std::list<Rock*> rocks;
	Gravity gravity;
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
			else if (event.type == sf::Event::MouseButtonPressed){
				auto mousePosition = wabi::screenToBrainSpace((sf::Vector2f)sf::Mouse::getPosition());
				auto rock = new Rock(50);
				rock->position = mousePosition;
				rocks.push_back(rock);
			}
        }
        window.clear(sf::Color::Black);

		if (timeSinceLastFixedUpdate >= fixedTimeStep) {
			timeSinceLastFixedUpdate = 0.0f;
			sea.fixedUpdate();
			// TODO: make an object pool/manager that can do this. (just like a sea is sort of a wave pool)
			// Then again there will probably never be too many rocks in a game once there are rules and things.
			// w/e we'll figure it out
			for (auto it = rocks.begin(); it != rocks.end(); ++it) {
				auto rock = *it;
				gravity.apply(*rock);
				rock->fixedUpdate();
				if (rock->position.y > SCREEN_HEIGHT || rock->position.x > SCREEN_WIDTH || rock->position.x < 0 || rock->position.y < 0) {
					it = rocks.erase(it);
					if (it == rocks.end())
						break;
					// it = rocks.(rock);
					delete rock;
				}
			}
		}
		if (time.totalTime.count() > 1) {
		// 	blah(sea);
		}

        infostream << "FrameRate    : " << 1 / time.deltaTime.count() << std::endl;
		infostream << "deltaTime    : " << time.deltaTime.count() << std::endl;

		infostream << "totalTime    : " << time.totalTime.count() << std::endl;
		infostream << "# waves		: " << sea.waves.size() << std::endl;
		infostream << "# rocks		: " << rocks.size() << std::endl;
		infoText.setString(infostream.str());
		infoText.setPosition(3, 3);
		infoText.setColor(sf::Color::White);
		window.draw(infoText);
		// window << wave;
		window << sea;
		for (auto&& rock : rocks) {
			window << (*rock);
		}
        window.display();
    }
    return 0;
}
