#include <iostream>
#include <sstream>

#include "graphics.hpp"
#include "game.hpp"
#include "sea.hpp"
#include "ship.hpp"
#include "wave.hpp"
#include "rock.hpp"
#include "rect.hpp"


Graphics::Graphics(Game* g, sf::RenderTarget* rt) : font(new sf::Font()), text(new sf::Text()), game(g), target(rt) {
	font->loadFromFile("assets/fonts/IBMPlexMono-Regular.ttf");
	text->setFont(*Graphics::font);
	text->setColor(sf::Color::White);
	text->setCharacterSize(15);
	pixelsPerUnit = SCREEN_WIDTH / game->worldWidth;
}

Graphics::~Graphics() {
	delete font;
	delete text;
}

void Graphics::draw() const {
	target->clear(sf::Color::Black);
	draw(*game->sea);
	for (auto&& rock : game->rocks) {
		draw(*rock);
	}
	draw(*game->ship);

	std::stringstream infostream;
	infostream << "FrameRate    : " << 1 / wabi::Time::deltaTime.count() << std::endl;
	infostream << "deltaTime    : " << wabi::Time::deltaTime.count() << std::endl;
	infostream << "totalTime    : " << wabi::Time::totalTime.count() << std::endl;
	infostream << "# waves		: " << game->waves.size() << std::endl;
	infostream << "# rocks		: " << game->rocks.size() << std::endl;
	infostream << "# colliders	: " << game->collisionSystem.size() << std::endl;
	std::stringstream colliderPairStream;
	for (auto&& p : game->collisionSystem.pairs) {
		Collider c = p.second;
		colliderPairStream << "(" << c.pair.first->id << ", " << c.pair.second->id << ") ";
	}
	infostream << "pairs		: " << colliderPairStream.str() << std::endl;
	infostream << "ship pos		: " << game->ship->position << std::endl;
	infostream << "ship vel		: " << game->ship->velocity << std::endl;
	infostream << "ship accl	: " << game->ship->acceleration << std::endl;

	text->setString(infostream.str());
	text->setPosition(3, 3);
	target->draw(*text);

#if _DEBUG
	draw(game->collisionSystem);
#endif
}

void Graphics::draw(const CollisionSystem& collisionSystem) const {
	for (auto&& collider : collisionSystem.colliders()) {
		draw(*collider, sf::Color::Green);
	}
	for (auto&& pair : collisionSystem.pairs) {		
		Collider c = pair.second;
		if (c.colliding())
		{
			draw(*c.pair.first, sf::Color::Red);
			draw(*c.pair.second, sf::Color::Red);
		}
	}
}

void Graphics::draw(const Sea& sea) const {
	static std::vector<sf::Vertex> vertices;
	// for (int i = 0; i < SCREEN_WIDTH; i += 1) {
	float step = 1 / pixelsPerUnit;
	for (float i = 0; i < game->worldWidth; i += step) {
		vertices.push_back(sf::Vertex(brainToScreenSpace(sf::Vector2f(i, sea.height(i))*pixelsPerUnit), SEA_COLOR));
		vertices.push_back(sf::Vertex(sf::Vector2f(i*pixelsPerUnit, SCREEN_HEIGHT), SEA_COLOR));
	}
	target->draw(&vertices[0], vertices.size(), sf::TriangleStrip);
	vertices.clear();
}

void Graphics::draw(const Rock& rock) const {
	static sf::CircleShape shape(rock.radius);
	shape.setOutlineThickness(4);
	shape.setOutlineColor(sf::Color(204, 51, 0));
	shape.setFillColor(sf::Color(0, 0, 0, 0));
	shape.setOrigin(sf::Vector2f(rock.radius, rock.radius));
	shape.setPosition(brainToScreenSpace(rock.position));
	target->draw(shape);
}

void Graphics::draw(const Ship& ship) const {
	// screenRect.left = shipRect.left * 15;
	// screenRect.top = SCREEN_HEIGHT - (shipRect.top * 15);
	draw(game2ScreenRect(ship.rect()), sf::Color::Magenta);
}

void Graphics::draw(const Collidable& collider, sf::Color color) const {
	auto screenRect = game2ScreenRect(collider.rect());
	draw(screenRect, color);
	// text->setString(std::to_string(collider.id));
	// text->setPosition(brainToScreenSpace(sf::Vector2f(rect.left + rect.width / 2, rect.top - rect.height / 2)));
	// text->setColor(sf::Color::White);
	// target->draw(*text);
}


template <typename T>
void Graphics::draw(const wabi::Rect<T>& rect, sf::Color color) const {
	auto screenRect = game2ScreenRect(rect);
	static sf::RectangleShape rectShape;
	rectShape.setOutlineColor(color);
	rectShape.setOutlineThickness(3);
	rectShape.setFillColor(sf::Color(0, 0, 0, 0));
	rectShape.setSize(sf::Vector2f(screenRect.width, screenRect.height));
	rectShape.setPosition(sf::Vector2f(rect.left, rect.top));
	target->draw(rectShape);
}

template <typename T>
void Graphics::draw(const sf::Rect<T>& rect, sf::Color color) const {
	static sf::RectangleShape rectShape;
	rectShape.setOutlineColor(color);
	rectShape.setOutlineThickness(3);
	rectShape.setFillColor(sf::Color(0, 0, 0, 0));
	rectShape.setSize(sf::Vector2f(rect.width, rect.height));
	rectShape.setPosition(sf::Vector2f(rect.left, rect.top));
	target->draw(rectShape);
}
template<typename T>
sf::Vector2<T> Graphics::game2ScreenPos(const sf::Vector2<T>& v) const {
	return sf::Vector2<T>(v.x * pixelsPerUnit, SCREEN_HEIGHT-(v.y * pixelsPerUnit));
}

template<typename T>
sf::Vector2<T> Graphics::screen2GamePos(const sf::Vector2<T>& v) const {
	return sf::Vector2<T>(v.x, std::abs(SCREEN_HEIGHT - v.y)) / pixelsPerUnit;
}


template<typename T>
sf::Rect<T> Graphics::game2ScreenRect(const wabi::Rect<T>& in) const {
	return sf::Rect<T>(game2ScreenPos(sf::Vector2<T>(in.left, in.top)), sf::Vector2<T>(in.width * pixelsPerUnit, in.height * pixelsPerUnit));
}

