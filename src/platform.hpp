#pragma once

#include "utils.hpp"
#include "prelude.hpp"
#include "physicsbody.hpp"


class Platform : public PhysicsBody {
public:
	Platform() {}
	virtual ~Platform() {}

	float height;
	float width;
};
