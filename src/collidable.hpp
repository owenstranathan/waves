#pragma once

#include "utils.hpp"
#include "prelude.hpp"
#include "gameobject.hpp"
#include "collisionsystem.hpp"

class Collidable : public GameObject{
public:
	virtual void accept(Visitor& v);
	virtual void accept(CollisionVisitor& v, Collidable* c);
	virtual void resolveCollision(Collidable* c);
	virtual void resolveCollision(Sea* c);
	virtual void resolveCollision(Ship* c);
	virtual void resolveCollision(Rock* c);
	virtual void resolveCollision(Wave* c);
	virtual wabi::Rectf rect() const = 0;
};
