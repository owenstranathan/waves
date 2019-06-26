#pragma once

#include "utils.hpp"
#include "prelude.hpp"
#include "collidable.hpp"


class PhysicsBody : public Collidable {
public:
	virtual void update(const wabi::duration&);
	virtual sf::Vector2f dragForce(const float);
	inline float mass() { return rect().area() * density;  }
	void addForce(const sf::Vector2f&);

	bool useGravity = true;
	float density = 1;
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
};

