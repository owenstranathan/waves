#pragma once

#include <list>

#include "prelude.hpp"
#include "utils.hpp"
#include "collidable.hpp"


class Sea : public Collidable {
public:
	Sea(Game*, float);
	virtual ~Sea();

	virtual void collisionEnter(Ship* c) override;
	virtual void collisionStay(Ship* c) override;
	virtual void collisionEnter(Rock* c) override;
	virtual void collisionStay(Rock* c) override;


	virtual void accept(Visitor&)override;
	virtual void accept(CollisionVisitor&, Collidable*) override;
	virtual void update(const float) override;
	virtual wabi::Rectf rect() const override;

	float height(float x) const;
	float slope(float x) const;

	float level;
	Game* game;
};


