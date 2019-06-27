#pragma once

#include "utils.hpp"
#include "prelude.hpp"
#include "gameobject.hpp"
#include "collisionsystem.hpp"

class Collidable : public GameObject{
public:
	virtual ~Collidable() { }
	virtual void accept(Visitor& v);
	virtual void accept(CollisionVisitor& v, Collidable* c);
	virtual void collisionEnter(Collidable* c);
	virtual void collisionEnter(Sea* c);
	virtual void collisionEnter(Ship* c);
	virtual void collisionEnter(Rock* c);
	virtual void collisionEnter(Wave* c);

	virtual void collisionStay(Collidable* c);
	virtual void collisionStay(Sea* c);
	virtual void collisionStay(Ship* c);
	virtual void collisionStay(Rock* c);
	virtual void collisionStay(Wave* c);

	virtual void collisionExit(Collidable* c);
	virtual void collisionExit(Sea* c);
	virtual void collisionExit(Ship* c);
	virtual void collisionExit(Rock* c);
	virtual void collisionExit(Wave* c);

	virtual wabi::Rectf rect() const = 0;
};
