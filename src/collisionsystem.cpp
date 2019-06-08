#include "collisionsystem.hpp"
#include "collidable.hpp"
#include "sea.hpp"
#include "wave.hpp"
#include "rock.hpp"


CollisionSystem::CollisionSystem(Game* g) : game(g) {}

void CollisionSystem::addCollider(Collidable* collider) {
	wabi::insert_sorted(colliders, collider, [](Collidable * a, Collidable * b)->bool { return a->rect().left < b->rect().left; });
}

std::list<Collidable*>::iterator CollisionSystem::removeCollider(std::list<Collidable*>::iterator it) {
	return colliders.erase(it);
}

std::list<Collidable*>::iterator CollisionSystem::removeCollider(Collidable* collider) {
	auto search = std::find(colliders.begin(), colliders.end(), collider);
	return (search != colliders.end()) ? removeCollider(search) : colliders.end();
}

std::list<std::pair<Collidable*, Collidable*>> CollisionSystem::activeColliderPairs() const {
	// Uses broad phase sweep and prune to determine a rough list of active Collidable pairs
	std::list<std::pair<Collidable*, Collidable*>> pairs;
	std::list<Collidable*> activeColliders;
	activeColliders.push_back(*colliders.begin());
	for (auto c = std::next(colliders.begin()); c != colliders.end(); std::advance(c, 1)) {
		std::list<Collidable*> stillActive;
		auto collider = *c;
		for (Collidable* active : activeColliders) {
			if (collider->rect().intersects(active->rect())) {
				pairs.push_back(std::make_pair(collider, active));
				stillActive.push_back(active);
			}
		}
		activeColliders.clear();
		activeColliders.swap(stillActive);
		stillActive.clear();
		activeColliders.push_back(collider);
	}
	return pairs;
}

void CollisionSystem::resolveCollisions() {
	std::list<std::pair<Collidable*, Collidable*>> activePairs = activeColliderPairs();
	for (auto&& pair : activePairs) {	
		// TODO: use visitor patternt to get dynamic types and do finer collision check
		resolveSingleCollision(pair.first, pair.second);
	}
}

template <typename T>
void resolveGenericCollision(T * a, Collidable*b){
	if (Sea * sea = dynamic_cast<Sea*>(b)) {
		a->resolveCollision(sea);
	}
	else if (Wave * wave = dynamic_cast<Wave*>(b)){
		a->resolveCollision(wave);
	}
	else if (Rock * rock = dynamic_cast<Rock*>(b)) {
		a->resolveCollision(rock);
	} 
}

void CollisionSystem::resolveSingleCollision(Collidable* a, Collidable* b) {
	if (Sea * sea = dynamic_cast<Sea*>(a)) {
		resolveGenericCollision(sea, b);
	}
	else if (Wave * wave = dynamic_cast<Wave*>(a)){
		resolveGenericCollision(wave, b);
	}
	else if (Rock * rock = dynamic_cast<Rock*>(a)) {
		resolveGenericCollision(rock, b);
	} 
}
