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

namespace wabi{
	template <typename T>
	bool collides(sf::Rect<T> a, sf::Rect<T>b) {
		return b.contains(b.left, b.top) && b.contains(b.left + b.width, b.top - b.height) || 
			a.contains(a.left, a.top) && a.contains(a.left + a.width, a.top - a.height) || 
			a.intersects(b) && b.intersects(a);
	}
}

