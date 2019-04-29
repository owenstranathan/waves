#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <SFML/Graphics.hpp>

#include "utils.hpp"
#include "wave.hpp"

using namespace std;
using namespace wabisoft;
using namespace sf;

int SCREEN_MULT = 80;
// int SCREEN_HEIGHT = 9 * SCREEN_MULT;
// int SCREEN_WIDTH = 16 * SCREEN_MULT;
int SCREEN_HEIGHT;
int SCREEN_WIDTH;

chrono::duration<float> deltaTime;

int main()
{
    ContextSettings settings;
    settings.antialiasingLevel = 10;
    auto videoMode = VideoMode::getDesktopMode();
	SCREEN_HEIGHT = videoMode.height;
	SCREEN_WIDTH = videoMode.width;
	sf::Text infoText;
	sf::Font font;
	font.loadFromFile("assets/fonts/IBMPlexMono-Regular.ttf");
	infoText.setFont(font);
	stringstream infostream;
    RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Blah!", Style::Default, settings);
    window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(100);
    auto start = chrono::system_clock::now();
    auto end = start; 
    // run the program as long as the window is open
    int frames = 0;
	duration time(0);
	float fixedTimeStep = 0.02f;
	float timeSinceLastFixedUpdate = 0.0f;

	Wave wave;
	wave.transform.scale(100, 100);
	
	// game loop
    while (window.isOpen())
    {
		infostream.str(string());
        start = keepTime(start);
		frames++;
		time += deltaTime;
	    timeSinceLastFixedUpdate += deltaTime.count();
        // check all the window's events that were triggered since the last iteration of the loop
        Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear(Color::White);

		if (timeSinceLastFixedUpdate >= fixedTimeStep)
			timeSinceLastFixedUpdate = 0.0f;

		auto avg = frames / time.count();
		if (frames > 100) {
			frames = 0;
			time = duration(0);
		}

        infostream << "FrameRate: " <<  avg << endl;
		infostream << "deltaTime: " << deltaTime.count() << endl;
		infoText.setString(infostream.str());
		infoText.setPosition(3, 3);
		infoText.setColor(sf::Color::Magenta);
		window.draw(infoText);
		wave.draw(window);
        window.display();
    }
    return 0;
}
