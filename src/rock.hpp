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

	virtual void resolveCollision(Sea*) override;
	virtual void accept(Visitor&) override;
	virtual void accept(CollisionVisitor&, Collidable*) override;
	virtual wabi::Rectf rect() const override;
	virtual void update(const wabi::duration&) override;

	float radius;
	bool hitWater = false;
};

