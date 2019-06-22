#include "collisionsystem.hpp"
#include "collidable.hpp"
#include "game.hpp"
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

// std::list<std::pair<Collidable*, Collidable*>> CollisionSystem::activeColliderPairs() const {
void CollisionSystem::activeColliderPairs() {
	// Uses broad phase sweep and prune to determine a rough list of active Collidable pairs
	pairs.clear();
	if (colliders.size() < 2) {
		return;
	}
	float maxX = (*colliders.begin())->rect().right();
	for (auto c = std::next(colliders.begin()); c != colliders.end(); c = std::next(c)) {
		auto collider = *c;
		auto colliderRect = collider->rect();
		auto a = c;
		do {
			a = std::prev(a);
			auto active = *a;
			auto activeRect = active->rect();
			if (activeRect.intersects(colliderRect)) {
				pairs.push_back(std::make_pair(collider, active));
			}
			if (colliderRect.left > maxX) {
				break;
			}
		} while (a != colliders.begin());
		if (colliderRect.right() > maxX) {
			maxX = colliderRect.right();
		}
	}
}

void CollisionSystem::resolveCollisions() {
	wabi::insertion_sort<Collidable*>(colliders.begin(), colliders.end(), [](Collidable * a, Collidable * b)->bool { return a->rect().left < b->rect().left; });
	activeColliderPairs();
	game->log << pairs.size() << " collision pairs." << std::endl;
	for (auto&& pair : pairs) {	
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

void CollisionSystem::clear() {
	colliders.clear();
}
