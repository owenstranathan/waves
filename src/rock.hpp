#pragma once

#include "utils.hpp"
#include "physicsbody.hpp"

static const float ROCK_MASS = 5.f;


class Rock : public PhysicsBody {
public:
	Rock(Game* g, float r): game(g), radius(r) {
		mass = ROCK_MASS;
	}

	virtual void* resolveCollision(Collidable*);
	virtual void* resolveCollision(Sea*);
	virtual void* resolveCollision(Rock*);
	virtual void * accept(Visitor&);
	virtual wabi::Rectf rect() const;
	virtual void update(wabi::duration);

	Game* game;
	float radius;
	bool hitWater = false;
};

