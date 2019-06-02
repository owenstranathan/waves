#ifndef PHYSICSBODY_HPP
#define PHYSICSBODY_HPP

#include <SFML/System.hpp>
#include "collidable.hpp"
#include "utils.hpp"

class PhysicsBody : public Collidable {
public:
	virtual void fixedUpdate();

	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
};

#endif // !PHYSICSBODY_HPP
