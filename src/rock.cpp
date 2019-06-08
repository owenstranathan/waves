#include <iostream>
#include "utils.hpp"
#include "rock.hpp"
#include "sea.hpp"
#include "visitor.hpp"


void* Rock::resolveCollision(Collidable* collider) {
	return nullptr;
}

void* Rock::resolveCollision(Sea* sea) {
	if (position.y < sea->level && ! hitWater) {
		hitWater = true;
		auto mag = wabi::magnitude(velocity) * 50;
		return sea->createWave(position.x, mag);
	}
	return nullptr;
}

void* Rock::resolveCollision(Rock* rock) {
	return nullptr;
}





void * Rock::accept(Visitor& v) { return v.visit(this); }

sf::FloatRect Rock::rect() const {
	return sf::Rect<float>(position.x - radius, position.y + radius, radius, radius);
}


