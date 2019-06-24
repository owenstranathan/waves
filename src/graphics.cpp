#include <iostream>
#include <sstream>

#include "graphics.hpp"
#include "game.hpp"
#include "sea.hpp"
#include "ship.hpp"
#include "wave.hpp"
#include "rock.hpp"
#include "rect.hpp"


sf::Font * const Graphics::font = new sf::Font();
sf::Text* const Graphics::text = new sf::Text();
float Graphics::worldToScreenRatio = 1;

void Graphics::init() {
	// font = new sf::Font();
	font->loadFromFile("assets/fonts/IBMPlexMono-Regular.ttf");
	text->setFont(*Graphics::font);
	text->setColor(sf::Color::White);
	text->setCharacterSize(15);
	worldToScreenRatio = SCREEN_WIDTH * 0.00256;
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
	infostream << "# colliders	: " << game.collisionSystem.size() << std::endl;
	// std::stringstream colliderOrderStream;
	// for (auto&& c : game.collisionSystem.colliders) {
	// 	colliderOrderStream << c->id << " " ;
	// }
	// infostream << "x order		: " << colliderOrderStream.str() << std::endl;

	std::stringstream colliderPairStream;
	for (auto&& p : game.collisionSystem.pairs) {
		Collider c = p.second;
		colliderPairStream << "(" << c.pair.first->id << ", " << c.pair.second->id << ") ";
	}
	infostream << "pairs		: " << colliderPairStream.str() << std::endl;
	infostream << "ship pos		: " << game.ship->position.x << ", " << game.ship->position.y << std::endl;

	Graphics::text->setString(infostream.str());
	Graphics::text->setPosition(3, 3);
	rt.draw(*Graphics::text);

	// Graphics::text->setString(game.log.str());
	// sf::FloatRect textBounds = Graphics::text->getLocalBounds();
	// Graphics::text->setPosition(SCREEN_WIDTH - (textBounds.width+20), (SCREEN_HEIGHT/2) - textBounds.height);
	// rt.draw(*Graphics::text);
	rt << game.collisionSystem;
	rt << *game.ship;
	return rt;
}

sf::RenderTarget& operator<<(sf::RenderTarget& rt, const CollisionSystem& collisionSystem)
{
	for (auto&& collider : collisionSystem.colliders()) {
		draw(rt, *collider, sf::Color::Green);
	}
	// for (auto&& pair : collisionSystem.activeColliderPairs()) {		
	for (auto&& pair : collisionSystem.pairs) {		
		Collider c = pair.second;
		if (c.colliding())
		{
			draw(rt, *c.pair.first, sf::Color::Red);
			draw(rt, *c.pair.second, sf::Color::Red);
		}
	}
	return rt;
}

sf::RenderTarget& operator<<(sf::RenderTarget& rt, const Sea& sea) {
	static std::vector<sf::Vertex> vertices;
	for (int i = 0; i < SCREEN_WIDTH; i += 1) {
		vertices.push_back(sf::Vertex(brainToScreenSpace(sf::Vector2f(i, (int)sea.height(i))), SEA_COLOR));
		vertices.push_back(sf::Vertex(sf::Vector2f(i, SCREEN_HEIGHT), SEA_COLOR));
	}
	rt.draw(&vertices[0], vertices.size(), sf::TriangleStrip);
	vertices.clear();

	// auto rect = sea.rect();
	// static sf::RectangleShape r(sf::Vector2f(rect.width, rect.height));
	// r.setOutlineColor(sf::Color::Red);
	// r.setOutlineThickness(3);
	// r.setFillColor(sf::Color(0,0,0,0));
	// r.setPosition(brainToScreenSpace(sf::Vector2f(rect.left, rect.top)));
	// rt.draw(r);

	// static sf::CircleShape point;
	// point.setRadius(5);
	// point.setFillColor(sf::Color::Red);
	// point.setOrigin(sf::Vector2f(2.5f, 2.5f));
	// for (auto&& wave : sea.game->waves) {
	// 	point.setPosition(brainToScreenSpace(wave->position));
	// 	rt.draw(point);
	// }
		// rt.draw(&vertices[0], vertices.size(), sf::LineStrip);
	return rt;
}

sf::RenderTarget& operator<<(sf::RenderTarget& rt, const Wave& wave) {		
	// static sf::CircleShape point(3);
	// point.setFillColor(sf::Color::Blue);
	// for (int i = 0; i < wave.num_vertices; i++) {
	// 	point.setPosition(brainToScreenSpace(wave.vertices[i]));
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
	shape.setPosition(brainToScreenSpace(rock.position));
	rt.draw(shape);
	return rt;
}

sf::RenderTarget& operator<<(sf::RenderTarget& rt, const Ship& ship)
{
	// drawRect(rt, ship.rect(), sf::Color::Magenta);
	// static sf::RectangleShape rectShape;
	// rectShape.setOutlineColor(sf::Color::Magenta);
	// rectShape.setOutlineThickness(3);
	// rectShape.setFillColor(sf::Color(0, 0, 0, 0));
	// auto rect = ship.rect();
	// auto size = toScreen(sf::Vector2f(rect.width, rect.height));
	// auto pos = toScreen(sf::Vector2f(rect.left, rect.top));
	// rectShape.setSize(size);
	// rectShape.setPosition(pos);
	// rt.draw(rectShape);
	return rt;
}

void draw(sf::RenderTarget& rt, const Collidable& collider, sf::Color color) {
	static sf::RectangleShape rectShape;
	rectShape.setOutlineColor(color);
	rectShape.setOutlineThickness(3);
	rectShape.setFillColor(sf::Color(0, 0, 0, 0));
	auto rect = collider.rect();
	rectShape.setSize(sf::Vector2f(rect.width, rect.height));
	rectShape.setPosition(brainToScreenSpace(sf::Vector2f(rect.left, rect.top)));
	rt.draw(rectShape);
	Graphics::text->setString(std::to_string(collider.id));
	Graphics::text->setPosition(brainToScreenSpace(sf::Vector2f(rect.left + rect.width / 2, rect.top - rect.height / 2)));
	Graphics::text->setColor(sf::Color::White);
	rt.draw(*Graphics::text);
}


template <typename T>
void drawRect(sf::RenderTarget& rt, const wabi::Rect<T>& rect, sf::Color color) {
	static sf::RectangleShape rectShape;
	rectShape.setOutlineColor(color);
	rectShape.setOutlineThickness(3);
	rectShape.setFillColor(sf::Color(0, 0, 0, 0));
	rectShape.setSize(sf::Vector2f(rect.width, rect.height));
	rectShape.setPosition(brainToScreenSpace(sf::Vector2f(rect.left, rect.top)));
	rt.draw(rectShape);
}


