#ifndef GRAVITY_HPP
#define GRAVITY_HPP

#include <vector>

#include "physicsbody.hpp"
#include "utils.hpp"


class Gravity {
public:
	Gravity() {}
	~Gravity() {}

	inline void apply(PhysicsBody& pb, wabi::duration deltaTime) {
		pb.velocity += sf::Vector2f(0, constant * deltaTime.count());
	}

	const float constant = -9.8f;
};

#endif // !GRAVITY_HPP
