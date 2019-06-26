#include <iostream>

#include "game.hpp"
#include "gravity.hpp"
#include "sea.hpp"
#include "ship.hpp"
#include "rect.hpp"
#include "utils.hpp"
#include "wave.hpp"


Ship::Ship(Game* g, sf::Vector2f p, float w, float h) : width(w), height(h) { game = g; position = p; density = 2.f; }

Ship::Ship(Game* g, sf::Vector2f p, sf::Vector2f size) : width(size.x), height(size.y) { game = g; position = p;  density = 2.f; }

Ship::~Ship() { }


void Ship::accept(Visitor& v) {
	return v.visit(this);
}

void Ship::accept(CollisionVisitor& v, Collidable* c)
{
	v.visit(this, c);
}

void Ship::update(const float deltaTime)
{
	Gravity::apply(*this, deltaTime);
	addForce(dragForce(0.1225f)); // always drag for air I guess, maybe we don't need this, but let's keep it for now.
	PhysicsBody::update(deltaTime);	
}

wabi::Rectf Ship::rect() const
{
	return wabi::Rectf(position.x-(width/2.f), position.y+(height/2.f), width, height);
}

void Ship::resolveCollision(Sea* sea) {
	wabi::Rectf overlap;
	rect().intersects(sea->rect(), overlap);
	auto g = Gravity::constant;
	addForce(sf::Vector2f(0, -g * overlap.height));
	addForce(dragForce(1));
}

void Ship::resolveCollision(Wave* wave) {
	auto waveHeight = wave->height(position.x) + game->sea->level;
	if (rect().bottom() > waveHeight)
		return;
	auto waveRect = wabi::Rectf(0, waveHeight, game->worldWidth, waveHeight);
	wabi::Rectf overlap;
	rect().intersects(waveRect, overlap);
	auto g = Gravity::constant;
	addForce(sf::Vector2f(0, -g *  overlap.height));
	// addForce(dragForce(1));
}



