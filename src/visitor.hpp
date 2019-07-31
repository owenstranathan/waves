#pragma once

#include "prelude.hpp"
#include "utils.hpp"


class Visitor {
public:
	virtual void visit(GameObject*) = 0;
	virtual void visit(Collidable*) = 0;
	virtual void visit(PhysicsBody*) = 0;
	virtual void visit(Sea*) = 0;
	virtual void visit(Wave*) = 0;
	virtual void visit(Rock*) = 0;
	virtual void visit(Platform*) = 0;
};
