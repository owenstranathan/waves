#include <iostream>

#include "game.hpp"
#include "gravity.hpp"
#include "platform.hpp"
#include "sea.hpp"
#include "ship.hpp"
#include "rect.hpp"
#include "utils.hpp"
#include "wave.hpp"

Ship::Ship(Game *g, sf::Vector2f p, float w, float h) : width(w), height(h)
{
	game = g;
	position = p;
	density = 2.f;
}

Ship::Ship(Game *g, sf::Vector2f p, sf::Vector2f size) : width(size.x), height(size.y)
{
	game = g;
	position = p;
	density = 2.f;
}

Ship::~Ship() {}

void Ship::accept(Visitor &v)
{
	return v.visit(this);
}

void Ship::accept(CollisionVisitor &v, Collidable *c)
{
	v.visit(this, c);
}

void Ship::update(const float deltaTime)
{
	Gravity::apply(*this, deltaTime);
	addForce(dragForce(0.1225f)); // always drag for air I guess, maybe we don't need this, but let's keep it for now.
	PhysicsBody::update(deltaTime);
	if (position.x > game->worldWidth || position.x < 0 || position.y < 0)
	{
		active = false;
	}
}

wabi::Rectf Ship::rect() const
{
	return wabi::Rectf(position.x - (width / 2.f), position.y + (height / 2.f), width, height);
}

void Ship::collisionEnter(Sea *sea)
{
	wabi::Rectf overlap;
	rect().intersects(sea->rect(), overlap);
	auto g = Gravity::constant;
	addForce(sf::Vector2f(0, -g * overlap.height));
	addForce(dragForce(1));
}

void Ship::collisionStay(Sea *sea)
{
	collisionEnter(sea);
}

void Ship::collisionEnter(Wave *wave)
{
	// Using the sea height here allows us to get the total cumulative wave height
	// at our position
	auto waveHeight = game->sea->height(position.x);
	// If we're above it then we just don't worry about it
	if (rect().bottom() > waveHeight)
	{
		return;
	}
	// W
	auto waveRect = wabi::Rectf(0, waveHeight, game->worldWidth, waveHeight);
	wabi::Rectf overlap;
	rect().intersects(waveRect, overlap);
	auto g = Gravity::constant;
	addForce(sf::Vector2f(0.5f * wave->velocity.x, -g * overlap.height));
	// addForce(sf::Vector2f(0.f, -g * overlap.height));
	// addForce(dragForce(1));
}

void Ship::collisionStay(Wave *wave)
{
	collisionEnter(wave);
}

void Ship::collisionEnter(Platform *platform)
{
	platform->collisionEnter(this);
}

void Ship::collisionStay(Platform *platform)
{
	platform->collisionStay(this);
}

void Ship::collisionExit(Platform *platform)
{
	platform->collisionExit(this);
}
