#include <cassert>

#include "collisionsystem.hpp"
#include "collidable.hpp"
#include "game.hpp"
#include "sea.hpp"
#include "wave.hpp"
#include "rock.hpp"

const auto by_x = [](Collidable * a, Collidable * b)->bool { return a->rect().left < b->rect().left; };
const auto by_y = [](Collidable * a, Collidable * b)->bool { return a->rect().top < b->rect().top; };


CollisionSystem::CollisionSystem(Game* g) : game(g) {}

void CollisionSystem::addCollider(Collidable* collidable) {
	wabi::insert_sorted(sortedByX, collidable, by_x);
	wabi::insert_sorted(sortedByY, collidable, by_y);
	// colliders.push_back(collidable);
}

void CollisionSystem::removeCollider(Collidable* collidable) {
	// colliders.remove(collidable);
	sortedByX.remove(collidable);
	sortedByY.remove(collidable);
	pairs.clear();
}

void CollisionSystem::SweepAxis(
	unsigned int axis,
	std::list<Collidable*>& colliders,
	std::function<bool(wabi::Rectf, wabi::Rectf)> compare,
	std::function<float(wabi::Rectf)> little,
	std::function<float(wabi::Rectf)> big) {
	// Uses broad phase sweep and prune to determine a rough list of active Collidable pairs
	if (colliders.size() < 2) {
		return;
	}
	float max = big((*colliders.begin())->rect());
	for (auto c = std::next(colliders.begin()); c != colliders.end(); c = std::next(c)) {
		auto collider = *c;
		auto colliderRect = collider->rect();
		auto a = c;
		do {
			a = std::prev(a);
			auto active = *a;
			auto activeRect = active->rect();
			// if (activeRect.intersects(colliderRect)) {
			if (compare(colliderRect, activeRect)){
				auto key = make_unordered_pair(collider->id, active->id);
				pairs[key].pair = std::make_pair(collider, active);
				pairs[key].mask |= axis;
				if (pairs[key].colliding()) {
					activePairs.push_back(pairs[key].pair);
				}
			}
			if (little(colliderRect) > max) {
				break;
			}
		} while (a != colliders.begin());
		if (big(colliderRect) > max) {
			max = big(colliderRect);
		}
	}
}

void CollisionSystem::resolveCollisions() {
	wabi::insertion_sort<Collidable*>(sortedByX.begin(), sortedByX.end(), by_x);
	wabi::insertion_sort<Collidable*>(sortedByY.begin(), sortedByY.end(), by_y);
	pairs.clear();
	activePairs.clear();
	SweepAxis(
		X_AXIS,
		sortedByX,
		[](wabi::Rectf r1, wabi::Rectf r2) -> bool { return r1.left < r2.right(); },
		[](wabi::Rectf r) -> float { return r.left; },
		[](wabi::Rectf r) -> float { return r.right(); });
	SweepAxis(
		Y_AXIS,
		sortedByY,
		[](wabi::Rectf r1, wabi::Rectf r2) -> bool { return r1.bottom() < r2.top; },
		[](wabi::Rectf r) -> float { return r.bottom(); },
		[](wabi::Rectf r) -> float { return r.top; });
	for (auto&& pair : activePairs) {	
		resolveSingleCollision(pair.first, pair.second);
		// TODO: use visitor patternt to get dynamic types and do finer collision check
		// resolveSingleCollision(pair.first, pair.second);
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
	// colliders.clear();
	sortedByX.clear();
	sortedByY.clear();
	pairs.clear();
}

size_t CollisionSystem::size() const {
	assert(sortedByX.size() == sortedByY.size());
	return sortedByX.size();
}
