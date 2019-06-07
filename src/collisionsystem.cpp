#include "collisionsystem.hpp"
#include "collidable.hpp"


void CollisionSystem::addCollider(Collidable* collider) {
	wabi::insert_sorted(colliders, collider, [](Collidable * a, Collidable * b)->bool { return a->rect().left < b->rect().left; });
}

std::list<std::pair<Collidable*, Collidable*>> CollisionSystem::activeColliderPairs() {
	// Uses broad phase sweep and prune to determine a rough list of active Collidable pairs
	std::list<std::pair<Collidable*, Collidable*>> pairs;
	std::list<Collidable*> activeColliders;
	activeColliders.push_back(*colliders.begin());
	for (auto c = std::next(colliders.begin()); c != colliders.end(); std::advance(c, 1)) {
		std::list<Collidable*> stillActive;
		auto collider = *c;
		for (Collidable * active : activeColliders) {
			if (collider->rect().intersects(active->rect())) {
				pairs.push_back(std::make_pair(collider, active));
				stillActive.push_back(active);
			}
			activeColliders.clear();
			activeColliders.swap(stillActive);
			stillActive.clear();
			activeColliders.push_back(collider);
		}
	}
	return pairs;
}

void CollisionSystem::resolveCollisions() {
	std::list<std::pair<Collidable*, Collidable*>> activePairs = activeColliderPairs();
	// CollisionVisitor v;
	for (auto&& pair : activePairs) {	
		// TODO: use visitor patternt to get dynamic types and do finer collision check
	}
}