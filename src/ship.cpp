#include "ship.hpp"

Ship::Ship(sf::Vector2f p, float w, float h) : width(w), height(h) { position = p; }

Ship::Ship(sf::Vector2f p, sf::Vector2f size) : width(size.x), height(size.y) { position = p;  }

Ship::~Ship() { }

void* Ship::resolveCollision(Collidable* c)
{
	return nullptr;
}


void Ship::update(wabi::duration deltaTime)
{
	// Call base class update to do all the kinematics and shit.
	PhysicsBody::update(deltaTime);	
}

sf::Rect<float> Ship::rect() const
{
	// We do eventually want to set the origin on the rect but for know I need this
	// return sf::Rect<float>(position.x-(width/2.f), position.y+(height/2.f), width, height);
	return sf::Rect<float>(position.x, position.y, width, height);
}
