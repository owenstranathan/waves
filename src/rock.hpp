#ifndef ROCK_HPP 
#define ROCK_HPP

#include "utils.hpp"
#include "physicsbody.hpp"

class Rock : public PhysicsBody {
public:
	Rock(): radius(0) {}
	Rock(float r): radius(r) {}

	inline sf::Rect<float> rect() {
		return sf::Rect<float>(position.x - radius, position.y + radius, radius, radius);
	}
	float radius;
};

#endif
