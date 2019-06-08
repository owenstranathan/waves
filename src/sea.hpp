#pragma once

#include <list>

#include "prelude.hpp"
#include "utils.hpp"
#include "collidable.hpp"


class Sea : public Collidable{
public:
	Sea(Game*, float);
	~Sea();

	virtual void* resolveCollision(Collidable*);
	virtual void* resolveCollision(Rock*);

	virtual void* accept(Visitor&);
	virtual void update(wabi::duration deltaTime);
	float height(float x) const;
	float slope(float x) const;
	sf::Rect<float> rect() const;

	// std::list<Wave*> waves;
	float level;
	Game* game;
};


