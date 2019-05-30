#ifndef ROCK_HPP 
#define ROCK_HPP

#include "utils.hpp"
#include "collidable.hpp"

class Rock : Collidable{
public:
	Rock(): radius(0) {}
	Rock(float r): radius(r) {}

	void fixedUpdate();
	sf::Rect<float> rect();

	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	float radius;
};

#endif
