#define _USE_MATH_DEFINES

#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <SFML/Graphics.hpp>

#include "utils.hpp"
#include "wave.hpp"


int SCREEN_MULT = 100;
int SCREEN_HEIGHT = 9 * SCREEN_MULT;
int SCREEN_WIDTH = 16 * SCREEN_MULT;
// int SCREEN_HEIGHT;
// int SCREEN_WIDTH;
;
// chrono::duration<float> deltaTime;

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
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Waves!", sf::Style::None, settings);
    window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(100);

    int frames = 0;
	float fixedTimeStep = 0.02f;
	float timeSinceLastFixedUpdate = 0.0f;

	Wave wave(1000, 1000);
	auto wavyboy = [wave](float x) -> float {
		return wave.magnitude* std::pow(M_E, -0.05 * wave.time * wave.time) * std::pow(std::sinf((1.0f / wave.magnitude) * M_PI * x - wave.time), 2);
	};
	wave.components.push_back(WavyBoyDefault(&wave));
	// game loop
    while (window.isOpen())
    {
		infostream.str(std::string());
        // start = keepTime(start);
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

		if (timeSinceLastFixedUpdate >= fixedTimeStep)
			timeSinceLastFixedUpdate = 0.0f;
			wave.fixedUpdate();

		auto avg = frames / time.totalTime.count();
		if (time.totalTime.count() > 1) {
			frames = 0;
			time.reset();
		}

		sf::Vector2f positions[3] = { sf::Vector2f(1, 1), sf::Vector2f((float)SCREEN_WIDTH/2, (float)SCREEN_HEIGHT/2), sf::Vector2f(SCREEN_WIDTH-1, SCREEN_HEIGHT-1)};
		sf::CircleShape circle(2);
		for (auto i = 0; i < 3; i++) {
			circle.setPosition(wabi::brainToScreenSpace(positions[i]));
			circle.setFillColor(sf::Color::Magenta);
			window.draw(circle);
		}
        infostream << "FrameRate    : " << avg << std::endl;
		infostream << "deltaTime    : " << time.deltaTime.count() << std::endl;
		infostream << "t            : " << wave.time << std::endl;
		infoText.setString(infostream.str());
		infoText.setPosition(3, 3);
		infoText.setColor(sf::Color::Magenta);
		window.draw(infoText);
		wave.draw(window);
        window.display();
    }
    return 0;
}
