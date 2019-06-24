#pragma once

#include <list>

#include "prelude.hpp"
#include "utils.hpp"
#include "collidable.hpp"


class Sea : public Collidable {
public:
	Sea(Game*, float);
	~Sea();

	virtual void resolveCollision(Sea* c) override;
	virtual void resolveCollision(Ship* c) override;
	virtual void resolveCollision(Rock* c) override;


	virtual void accept(Visitor&);
	virtual void accept(CollisionVisitor&, Collidable*);
	virtual void update(wabi::duration deltaTime);
	float height(float x) const;
	float slope(float x) const;
	wabi::Rectf rect() const;

	// std::list<Wave*> waves;
	float level;
	Game* game;

	// Inherited via Collidable
	};


