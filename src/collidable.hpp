#pragma once

#include "utils.hpp"
#include "prelude.hpp"
#include "gameobject.hpp"
#include "collisionsystem.hpp"

class Collidable : public GameObject{
public:
	virtual ~Collidable() { }
	virtual void accept(Visitor& v);
	virtual void accept(CollisionVisitor& v, Collidable*);
	virtual void collisionEnter(Collidable*);
	virtual void collisionEnter(Sea*);
	virtual void collisionEnter(Ship*);
	virtual void collisionEnter(Rock*);
	virtual void collisionEnter(Wave*);
	virtual void collisionEnter(Platform*);

	virtual void collisionStay(Collidable*);
	virtual void collisionStay(Sea*);
	virtual void collisionStay(Ship*);
	virtual void collisionStay(Rock*);
	virtual void collisionStay(Wave*);
	virtual void collisionStay(Platform*);

	virtual void collisionExit(Collidable*);
	virtual void collisionExit(Sea*);
	virtual void collisionExit(Ship*);
	virtual void collisionExit(Rock*);
	virtual void collisionExit(Wave*);
	virtual void collisionExit(Platform*);

	virtual wabi::Rectf rect() const = 0;
};
