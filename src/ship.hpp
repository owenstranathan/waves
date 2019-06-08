#pragma once

#include "utils.hpp"
#include "prelude.hpp"
#include "physicsbody.hpp"

class Ship : public PhysicsBody{
public:	
	Ship();
	~Ship();


	// Inherited via PhysicsBody
	virtual void* resolveCollision(Collidable* c);
	virtual void* resolveCollision(Rock * c);
	virtual void* resolveCollision(Sea * c);
	virtual void* resolveCollision(Wave * c);

	virtual void update(wabi::duration);

	virtual sf::Rect<float> rect() const;

};
