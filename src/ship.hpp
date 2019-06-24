#pragma once

#include "utils.hpp"
#include "prelude.hpp"
#include "physicsbody.hpp"

class Ship : public PhysicsBody{
public:	

	Ship(sf::Vector2f, float, float);
	Ship(sf::Vector2f, sf::Vector2f);
	~Ship();

	virtual void accept(Visitor&);
	virtual void accept(CollisionVisitor&, Collidable*);
	virtual void resolveCollision(Sea * c);
	virtual void update(wabi::duration);
	virtual wabi::Rectf rect() const;

	float width;
	float height;
};
