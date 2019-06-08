#include <iostream>
#include <sstream>

#include "graphics.hpp"
#include "game.hpp"
#include "sea.hpp"
#include "wave.hpp"
#include "rock.hpp"


sf::Font * const Graphics::font = new sf::Font();
sf::Text* const Graphics::text = new sf::Text();

void Graphics::init() {
	// font = new sf::Font();
	font->loadFromFile("assets/fonts/IBMPlexMono-Regular.ttf");
	text->setFont(*Graphics::font);
	text->setColor(sf::Color::White);
	text->setCharacterSize(15);
}

void Graphics::cleanUp() {
	delete font;
	delete text;
}

sf::RenderTarget& operator<<(sf::RenderTarget& rt, const Game& game) {
	rt.clear(sf::Color::Black);

	rt << *game.sea;
	for (auto&& rock : game.rocks) {
		rt << (*rock);
	}

	std::stringstream infostream;
	infostream << "FrameRate    : " << 1 / game.time.deltaTime.count() << std::endl;
	infostream << "deltaTime    : " << game.time.deltaTime.count() << std::endl;
	infostream << "totalTime    : " << game.time.totalTime.count() << std::endl;
	infostream << "# waves		: " << game.waves.size() << std::endl;
	infostream << "# rocks		: " << game.rocks.size() << std::endl;
	infostream << "# colliders	: " << game.collisionSystem.colliders.size() << std::endl;
	Graphics::text->setString(infostream.str());
	Graphics::text->setPosition(3, 3);
	rt.draw(*Graphics::text);

	Graphics::text->setString(game.log.str());
	if (game.log.str() != "") {
		std::cout << game.log.str();
	}
	sf::FloatRect textBounds = Graphics::text->getLocalBounds();
	Graphics::text->setPosition(SCREEN_WIDTH - (textBounds.width+20), 3);
	rt.draw(*Graphics::text);
	rt << game.collisionSystem;
	return rt;
}

void draw(sf::RenderTarget& rt, const Collidable& collider, sf::Color color) {
	static sf::RectangleShape rectShape;
	rectShape.setOutlineColor(color);
	rectShape.setOutlineThickness(3);
	rectShape.setFillColor(sf::Color(0, 0, 0, 0));
	auto rect = collider.rect();
	rectShape.setSize(sf::Vector2f(rect.width, rect.height));
	rectShape.setPosition(wabi::brainToScreenSpace(sf::Vector2f(rect.left, rect.top)));
	rt.draw(rectShape);
}

sf::RenderTarget& operator<<(sf::RenderTarget& rt, const CollisionSystem& collisionSystem)
{
	for (auto&& collider : collisionSystem.colliders) {
		draw(rt, *collider, sf::Color::Green);
	}
	for (auto&& pair : collisionSystem.activeColliderPairs()) {		
		draw(rt, *pair.first, sf::Color::Red);
		draw(rt, *pair.second, sf::Color::Red);
	}
	return rt;
}

sf::RenderTarget& operator<<(sf::RenderTarget& rt, const Sea& sea) {
	std::vector<sf::Vertex> vertices;
	for (int i = 0; i < SCREEN_WIDTH; i += 1) {
		vertices.push_back(sf::Vertex(wabi::brainToScreenSpace(sf::Vector2f(i, (int)sea.height(i))), SEA_COLOR));
		vertices.push_back(sf::Vertex(sf::Vector2f(i, SCREEN_HEIGHT), SEA_COLOR));
	}
	rt.draw(&vertices[0], vertices.size(), sf::TriangleStrip);

	// auto rect = sea.rect();
	// static sf::RectangleShape r(sf::Vector2f(rect.width, rect.height));
	// r.setOutlineColor(sf::Color::Red);
	// r.setOutlineThickness(3);
	// r.setFillColor(sf::Color(0,0,0,0));
	// r.setPosition(wabi::brainToScreenSpace(sf::Vector2f(rect.left, rect.top)));
	// rt.draw(r);

	// static sf::CircleShape point;
	// point.setRadius(5);
	// point.setFillColor(sf::Color::Red);
	// point.setOrigin(sf::Vector2f(2.5f, 2.5f));
	// for (auto&& wave : sea.game->waves) {
	// 	point.setPosition(wabi::brainToScreenSpace(wave->position));
	// 	rt.draw(point);
	// }
		// rt.draw(&vertices[0], vertices.size(), sf::LineStrip);
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

sf::RenderTarget& operator<<(sf::RenderTarget& rt, const Ship& ship)
{
	// static	sf::RectangleShape shape()
	return rt;
}

