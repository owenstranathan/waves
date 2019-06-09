#pragma once

#include "utils.hpp"
#include "prelude.hpp"
#include "physicsbody.hpp"

class Ship : public PhysicsBody{
public:	

	Ship(sf::Vector2f, float, float);
	Ship(sf::Vector2f, sf::Vector2f);
	~Ship();

	// Inherited via PhysicsBody
	virtual void* resolveCollision(Collidable* c);
	// virtual void* resolveCollision(Rock * c);
	// virtual void* resolveCollision(Sea * c);
	// virtual void* resolveCollision(Wave * c);

	virtual void update(wabi::duration);

	virtual sf::Rect<float> rect() const;

	float width;
	float height;
};
