#ifndef GRAVITY_HPP
#define GRAVITY_HPP

#include <vector>

#include "prelude.hpp"
#include "utils.hpp"


class Gravity {
public:
	Gravity(Game *);
	~Gravity();

	void apply(PhysicsBody& pb, wabi::duration deltaTime);

	static const float constant;

	Game* game;
};

#endif // !GRAVITY_HPP
