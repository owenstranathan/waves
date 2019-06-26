#pragma once

#include <vector>

#include "prelude.hpp"
#include "utils.hpp"


class Gravity {
public:

	static void apply(PhysicsBody& pb, const float deltaTime);
	static const sf::Vector2f force;
	static const float constant;
};

