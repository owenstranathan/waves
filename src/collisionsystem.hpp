# pragma once

#include "utils.hpp"
#include "prelude.hpp"


class CollisionSystem {
public:
	void resolveCollisions();
	std::list<std::pair<Collidable*, Collidable*>> activeColliderPairs();
	void addCollider(Collidable*);
	
	std::list<Collidable*> colliders;
};

// class CollisionVisitor : Visitor {
// 	void visit(Collidable* c);
// };

