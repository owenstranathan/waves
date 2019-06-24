#include <iostream>

#include "utils.hpp"
#include "ship.hpp"
#include "gravity.hpp"
#include "sea.hpp"
#include "rect.hpp"


Ship::Ship(sf::Vector2f p, float w, float h) : PhysicsBody(p), width(w), height(h) { density = 0.5f; }

Ship::Ship(sf::Vector2f p, sf::Vector2f size) : PhysicsBody(p), width(size.x), height(size.y) { density = 0.5f; }

Ship::~Ship() { }


void Ship::accept(Visitor& v) {
	return v.visit(this);
}

void Ship::accept(CollisionVisitor& v, Collidable* c)
{
	v.visit(this, c);
}

void Ship::update(wabi::duration deltaTime)
{
	// Call base class update to do all the kinematics and shit.
	PhysicsBody::update(deltaTime);	
	if (velocity.y / std::abs(velocity.y) > 0) {
		drag(1.2);
	}
	else {
		drag(0);
	}
}

wabi::Rectf Ship::rect() const
{
	// We do eventually want to set the origin on the rect but for know I need this
	return wabi::Rectf(position.x-(width/2.f), position.y+(height/2.f), width, height);
	// return wabi::Rectf(position.x, position.y, width, height);
}

void Ship::resolveCollision(Sea* s) {
	wabi::Rectf overlap;
	rect().intersects(s->rect(), overlap);
	sf::Vector2f buoyancy = sf::Vector2f();
	auto g = Gravity::constant;
	auto magic =  (1 / (0.1* std::max(width, height)));
	// buoyancy.y = 0.0475 * overlap.height * -g;
	buoyancy.y = magic * overlap.height * -g;
	// acceleration += buoyancy * wabi::Time::deltaTime.count();
	addForce(buoyancy);
	// drag(2);
	
	// auto dragForce = g/std::abs(g) * sf::Vector2f(0, velocity.y * velocity.y) * wabi::Time::deltaTime.count();
	// acceleration += dragForce;
}

