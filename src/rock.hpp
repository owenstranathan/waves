#ifndef ROCK_HPP 
#define ROCK_HPP

#include "utils.hpp"

class Rock {
public:
	Rock(): radius(0) {}
	Rock(float r): radius(r) {}

	void fixedUpdate();

	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	float radius;
};

#endif
