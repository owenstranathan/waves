# pragma once

#include "utils.hpp"
#include "prelude.hpp"
#include "visitor.hpp"


class CollisionSystem {
public:
	CollisionSystem(Game*);

	void resolveCollisions();
	void resolveSingleCollision(Collidable*, Collidable*);
	std::list<std::pair<Collidable*, Collidable*>> activeColliderPairs() const;
	void addCollider(Collidable*);
	std::list<Collidable*>::iterator removeCollider(std::list<Collidable*>::iterator);
	std::list<Collidable*>::iterator removeCollider(Collidable*);
	
	std::list<Collidable*> colliders;
	Game* game;
};

