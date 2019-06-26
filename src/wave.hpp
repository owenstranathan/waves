#pragma once

#include <vector>
#include <math.h>

#include "prelude.hpp"
#include "utils.hpp"
#include "collidable.hpp"

// TODO: make a wave management class (ObjectPool)

class Wave : public Collidable {
public:
	Wave(Game*, float, float);
	~Wave();

	float height(float x) const; 
	float slope(float x) const;
	float left() const;
	float right() const;

	virtual void accept(Visitor &)override ;
	virtual void accept(CollisionVisitor &, Collidable* c)override;
	virtual void update(const wabi::duration&) override;
	virtual wabi::Rectf rect() const override;

// Inherited via Collidable


	// Sea *sea;
	Game* game;
	sf::Vector2f position;
	float startX;
	float amplitude;
	float sign = 5.f;
	float time = 0;
	float width = 0.01;
	float decay = 0;
	// decay coefficient
};

