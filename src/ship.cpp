#include "ship.hpp"

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
	return sf::Rect<float>();
}
