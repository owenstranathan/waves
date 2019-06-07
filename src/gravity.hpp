#ifndef GRAVITY_HPP
#define GRAVITY_HPP

#include <vector>

#include "prelude.hpp"
#include "utils.hpp"


class Gravity {
public:
	Gravity();
	~Gravity();

	void apply(PhysicsBody& pb, wabi::duration deltaTime);

	const float constant = -9.8f;
};

#endif // !GRAVITY_HPP
