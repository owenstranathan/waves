#include <cassert>

#include "collisionsystem.hpp"
#include "collidable.hpp"
#include "game.hpp"
#include "sea.hpp"
#include "ship.hpp"
#include "wave.hpp"
#include "rock.hpp"

const auto by_x = [](Collidable * a, Collidable * b)->bool { return a->rect().left < b->rect().left; };
const auto by_y = [](Collidable * a, Collidable * b)->bool { return a->rect().top < b->rect().top; };


CollisionSystem::CollisionSystem(Game* g) : game(g) {}

void CollisionSystem::addCollider(Collidable* collidable) {
	wabi::insert_sorted(sortedByX, collidable, by_x);
	wabi::insert_sorted(sortedByY, collidable, by_y);
}

void CollisionSystem::removeCollider(Collidable* collidable) {
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
		CollisionVisitor v;
		pair.first->accept(v, pair.second);
	}
}

void CollisionSystem::clear() {
	sortedByX.clear();
	sortedByY.clear();
	pairs.clear();
}

size_t CollisionSystem::size() const {
	assert(sortedByX.size() == sortedByY.size());
	return sortedByX.size();
}

void CollisionVisitor::visit(Collidable* c1, Collidable* c2) {
	c1->resolveCollision(c2);
}

void CollisionVisitor::visit(PhysicsBody* pb, Collidable* c) {
	c->resolveCollision(pb);
}

void CollisionVisitor::visit(Sea* sea, Collidable* c) {
	c->resolveCollision(sea);
}

void CollisionVisitor::visit(Rock* rock, Collidable* c) {
	c->resolveCollision(rock);
}

void CollisionVisitor::visit(Wave* wave, Collidable* c) {
	c->resolveCollision(wave);
}

void CollisionVisitor::visit(Ship* ship, Collidable* c) {
	c->resolveCollision(ship);
}

