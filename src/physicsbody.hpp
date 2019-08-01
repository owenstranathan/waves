#pragma once

#include "utils.hpp"
#include "prelude.hpp"
#include "collidable.hpp"


class PhysicsBody : public Collidable {
public:
	virtual ~PhysicsBody() { }
	virtual void update(const float);
	virtual sf::Vector2f dragForce(const float);
	virtual float mass() const { return rect().area() * density;  }
	void addForce(const sf::Vector2f&);
	float impulse(const PhysicsBody&) const;

	bool useGravity = true;
    bool isKinematic = false;
    float density = 1;
	float coefficientOfRestitution = 0.05f;
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
};

