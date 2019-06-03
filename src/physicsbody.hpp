#ifndef PHYSICSBODY_HPP
#define PHYSICSBODY_HPP

#include <SFML/System.hpp>
#include "collidable.hpp"
#include "utils.hpp"
#include "game.hpp"

class PhysicsBody : public Collidable, public GameObject {
public:

	PhysicsBody();
	~PhysicsBody();

	virtual void fixedUpdate(wabi::duration deltaTime);

	float mass;
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
};

#endif // !PHYSICSBODY_HPP
