#include <iostream>
#include "utils.hpp"
#include "rock.hpp"
#include "sea.hpp"
#include "game.hpp"
#include "visitor.hpp"

void Rock::accept(Visitor& v) { return v.visit(this); }

void Rock::accept(CollisionVisitor& v, Collidable* c) { v.visit(this, c); }

wabi::Rectf Rock::rect() const {
	return wabi::Rectf(position.x - radius, position.y + radius, 2 * radius, 2 * radius);
}

void Rock::update(wabi::duration deltaTime)
{
	PhysicsBody::update(deltaTime);
	if (position.y > SCREEN_HEIGHT || position.x > SCREEN_WIDTH || position.x < 0 || position.y < 0) {
		active = false;
	}
}

void Rock::resolveCollision(Sea* sea) {
	if (position.y < sea->height(position.x) && !hitWater) {
		hitWater = true;
		auto mag = wabi::magnitude(velocity) * 25;
		game->createWave(position.x, mag);
	}
}

