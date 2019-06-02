#ifndef GRAVITY_HPP
#define GRAVITY_HPP

#include <vector>

#include "physicsbody.hpp"
#include "utils.hpp"


class Gravity {
public:
	Gravity() {}
	~Gravity() {}

	inline void apply(PhysicsBody& pb) {
		pb.acceleration += sf::Vector2f(0, constant * time.deltaTime.count());
	}

	const float constant = -9.8f;

	static wabi::Time time;
};

wabi::Time Gravity::time = wabi::Time();

#endif // !GRAVITY_HPP
