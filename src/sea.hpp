#pragma once

#include <list>

#include "prelude.hpp"
#include "utils.hpp"
#include "collidable.hpp"


class Sea : public Collidable {
public:
	Sea(Game*, float);
	~Sea();

	virtual void resolveCollision(Ship* c) override;
	virtual void resolveCollision(Rock* c) override;


	virtual void accept(Visitor&)override;
	virtual void accept(CollisionVisitor&, Collidable*) override;
	virtual void update(const wabi::duration&) override;
	virtual wabi::Rectf rect() const override;

	float height(float x) const;
	float slope(float x) const;

	float level;
	const float density = 19.7f;
	Game* game;
};


