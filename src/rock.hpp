#ifndef ROCK_HPP
#define ROCK_HPP

#include "utils.hpp"
#include "physicsbody.hpp"

static const float ROCK_MASS = 5.f;

class Rock : public PhysicsBody {
public:
	Rock(float r): radius(r) {
		mass = ROCK_MASS;
	}

	inline sf::Rect<float> rect() {
		return sf::Rect<float>(position.x - radius, position.y + radius, radius, radius);
	}
	float radius;
};

#endif // !ROCK_HPP
