# pragma once

#include "utils.hpp"
#include "prelude.hpp"
#include "visitor.hpp"


class CollisionSystem {
public:
	CollisionSystem(Game*);

	void resolveCollisions();
	void resolveSingleCollision(Collidable*, Collidable*);
	// std::list<std::pair<Collidable*, Collidable*>> activeColliderPairs() const;
	void activeColliderPairs();
	void addCollider(Collidable*);
	std::list<Collidable*>::iterator removeCollider(std::list<Collidable*>::iterator);
	std::list<Collidable*>::iterator removeCollider(Collidable*);
	void clear();
	
	std::list<Collidable*> colliders;
	std::list<std::pair<Collidable*, Collidable*>> pairs;
	Game* game;
};



