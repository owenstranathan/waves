#pragma once

#include "utils.hpp"
#include "physicsbody.hpp"

static const float ROCK_MASS = 5.f;


class Rock : public PhysicsBody {
public:
	Rock(Game* g, float r): radius(r) {
		game = g;
		density = 1;
	}
	virtual ~Rock() {}

	virtual void collisionEnter(Sea*) override;
	virtual void collisionStay(Sea*) override;
	virtual void accept(Visitor&) override;
	virtual void accept(CollisionVisitor&, Collidable*) override;
	virtual wabi::Rectf rect() const override;
	virtual void update(const float) override;
	virtual float mass() const override {
		return M_PI * radius* radius* density;
	}

	float radius;
	bool hitWater = false;
};

