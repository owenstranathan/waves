#include <iostream>
#include "utils.hpp"
#include "rock.hpp"
#include "sea.hpp"
#include "game.hpp"
#include "visitor.hpp"

int Rock::_seed_id = 0;

void* Rock::resolveCollision(Collidable* collider) {
	return nullptr;
}

void* Rock::resolveCollision(Sea* sea) {
	if (position.y < sea->height(position.x) && !hitWater) {
		hitWater = true;
		auto mag = wabi::magnitude(velocity) * 25;
		return game->createWave(position.x, mag);
	}
	return nullptr;
}

void* Rock::resolveCollision(Rock* rock) {
	return nullptr;
}


void * Rock::accept(Visitor& v) { return v.visit(this); }

sf::FloatRect Rock::rect() const {
	return sf::Rect<float>(position.x - radius, position.y + radius, 2 * radius, 2 * radius);
}

void Rock::update(wabi::duration deltaTime)
{
	PhysicsBody::update(deltaTime);
	if (position.y > SCREEN_HEIGHT || position.x > SCREEN_WIDTH || position.x < 0 || position.y < 0) {
		active = false;
	}
}


