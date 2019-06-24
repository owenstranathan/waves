#pragma once

#include "utils.hpp"
#include "prelude.hpp"
#include "collidable.hpp"


class PhysicsBody : public Collidable {
public:

	PhysicsBody();
	PhysicsBody(sf::Vector2f);
	~PhysicsBody();

	virtual void update(wabi::duration deltaTime);
	virtual void drag(float);
	inline float mass() { return rect().area() * density;  }
	inline void addForce(sf::Vector2f force) { acceleration += force * wabi::Time::deltaTime.count(); }

	bool useGravity = true;
	float density = 1;
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
};

