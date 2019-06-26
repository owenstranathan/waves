#include <iostream>

#include "game.hpp"
#include "gravity.hpp"
#include "sea.hpp"
#include "ship.hpp"
#include "rect.hpp"
#include "utils.hpp"


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

void Ship::update(const wabi::duration& deltaTime)
{
	// Call base class update to do all the kinematics and shit.
	// auto seaHeight = game->sea->height(position.x);
	// if (rect().bottom() < seaHeight) {
	// 	if (wabi::sign(velocity.y) < 0 || rect().top< seaHeight) {
	// 		auto drag = dragForce(game->sea->density);
	// 		addForce(drag);
	// 	}
	// 	else {
	// 		auto drag = dragForce(10.225f);
	// 		addForce(drag);
	// 	}
	// }
	PhysicsBody::update(deltaTime);	
	Gravity::apply(*this, deltaTime);
}

wabi::Rectf Ship::rect() const
{
	return wabi::Rectf(position.x-(width/2.f), position.y+(height/2.f), width, height);
}

void Ship::resolveCollision(Sea* s) {
	wabi::Rectf overlap;
	rect().intersects(s->rect(), overlap);
	// sf::Vector2f buoyancy = sf::Vector2f();
	auto g = Gravity::constant;
	// buoyancy.y = game->sea->density * overlap.height * -g;
	// addForce(buoyancy);	
	auto force = -1.f * velocity * -g;
	addForce(force);
}

