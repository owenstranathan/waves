#ifndef COLLIDABLE_HPP
#define COLLIDABLE_HPP

#include <vector>

#include "utils.hpp"

class Collidable {
public:
	virtual sf::Rect<float> rect() = 0;
};

class CollisionSystem {
	// TODO: port SAP to here.
};

#endif

