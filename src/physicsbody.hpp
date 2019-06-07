#ifndef PHYSICSBODY_HPP
#define PHYSICSBODY_HPP

#include "utils.hpp"
#include "prelude.hpp"
#include "collidable.hpp"


class PhysicsBody : public Collidable {
public:

	PhysicsBody();
	~PhysicsBody();

	virtual void accept(Visitor&);
	virtual void update(wabi::duration deltaTime);

	float mass;
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
};

#endif // !PHYSICSBODY_HPP
