#pragma once

#include "utils.hpp"
#include "physicsbody.hpp"

static const float ROCK_MASS = 5.f;


class Rock : public PhysicsBody {
public:
	Rock(Game* g, float r): radius(r) {
		game = g;
		density = 2;
	}

	virtual void resolveCollision(Sea*);
	virtual void accept(Visitor&);
	virtual void accept(CollisionVisitor&, Collidable*);
	virtual wabi::Rectf rect() const;
	virtual void update(wabi::duration);

	float radius;
	bool hitWater = false;
};

