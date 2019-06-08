#include <sstream>

#include "graphics.hpp"
#include "game.hpp"
#include "sea.hpp"
#include "wave.hpp"
#include "rock.hpp"


sf::Font * const Graphics::font = new sf::Font();

void Graphics::init() {
	// font = new sf::Font();
	font->loadFromFile("assets/fonts/IBMPlexMono-Regular.ttf");
}

void Graphics::cleanUp() {
	delete font;
}

sf::RenderTarget& operator<<(sf::RenderTarget& rt, const Game& game) {

	std::stringstream infostream;
	rt.clear(sf::Color::Black);
	infostream << "FrameRate    : " << 1 / game.time.deltaTime.count() << std::endl;
	infostream << "deltaTime    : " << game.time.deltaTime.count() << std::endl;

	infostream << "totalTime    : " << game.time.totalTime.count() << std::endl;
	infostream << "# waves		: " << game.sea->waves.size() << std::endl;
	infostream << "# rocks		: " << game.rocks.size() << std::endl;
	infostream << "# colliders	: " << game.collisionSystem.colliders.size() << std::endl;
	sf::Text infoText;
	infoText.setFont(*Graphics::font);
	infoText.setString(infostream.str());
	infoText.setPosition(3, 3);
	infoText.setColor(sf::Color::White);
	rt.draw(infoText);
	// window << wave;
	rt << *game.sea;
	for (auto&& rock : game.rocks) {
		rt << (*rock);
	}
	return rt;
}

sf::RenderTarget& operator<<(sf::RenderTarget& rt, const Sea& sea) {
	std::vector<sf::Vertex> vertices;
	for (int i = 0; i < SCREEN_WIDTH; i += 1) {
		vertices.push_back(sf::Vertex(wabi::brainToScreenSpace(sf::Vector2f(i, (int)sea.height(i))), SEA_COLOR));
		// vertices.push_back(sf::Vertex(sf::Vector2f(i, SCREEN_HEIGHT), SEA_COLOR));
	}
	// rt.draw(&vertices[0], vertices.size(), sf::TriangleStrip);
	rt.draw(&vertices[0], vertices.size(), sf::LineStrip);
	return rt;
}

sf::RenderTarget& operator<<(sf::RenderTarget& rt, const Wave& wave) {		
	// static sf::CircleShape point(3);
	// point.setFillColor(sf::Color::Blue);
	// for (int i = 0; i < wave.num_vertices; i++) {
	// 	point.setPosition(wabi::brainToScreenSpace(wave.vertices[i]));
	// 	rt.draw(point);
	// }
	return rt;
}

sf::RenderTarget& operator<<(sf::RenderTarget& rt, const Rock& rock) {
	static sf::CircleShape shape(rock.radius);
	shape.setOutlineThickness(4);
	shape.setOutlineColor(sf::Color(204, 51, 0));
	shape.setFillColor(sf::Color(0, 0, 0, 0));
	shape.setOrigin(sf::Vector2f(rock.radius, rock.radius));
	shape.setPosition(wabi::brainToScreenSpace(rock.position));
	rt.draw(shape);
	return rt;
}