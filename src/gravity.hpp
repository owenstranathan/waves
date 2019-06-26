#pragma once

#include <vector>

#include "prelude.hpp"
#include "utils.hpp"


class Gravity {
public:

	static void apply(PhysicsBody& pb, wabi::duration deltaTime);
	static const float constant;
};

