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

void CollisionSystem::addCollidable(Collidable* collidable) {
	wabi::insert_sorted(sortedByX, collidable, by_x);
	wabi::insert_sorted(sortedByY, collidable, by_y);
}

void CollisionSystem::removeCollidable(Collidable* collidable) {
	// Removing a collider invalidates the current active pairs list, and this method will clear it
	sortedByX.remove(collidable);
	sortedByY.remove(collidable);
	for (auto key : key2Id[collidable->id]) {
		// remove the key from the colliders (because the pair is not invalid)
		colliders.erase(key);
		// get the id for the other collider in this key pair;
		unsigned int otherId = (key.first == collidable->id) ? key.second : key.first;
		key2Id[otherId].remove(key);
	}
	key2Id.erase(collidable->id);
	// activePairs.clear();
}

void CollisionSystem::SweepAxis(
	unsigned int axis,
	std::list<Collidable*>& collidables,
	std::function<bool(wabi::Rectf, wabi::Rectf)> compare,
	std::function<float(wabi::Rectf)> little,
	std::function<float(wabi::Rectf)> big) {
	// Uses broad phase sweep and prune to determine a rough list of active Collidable pairs
	if (collidables.size() < 2) {
		return;
	}
	float max = big((*collidables.begin())->rect());
	for (auto c = std::next(collidables.begin()); c != collidables.end(); c = std::next(c)) {
		auto collidable = *c;
		auto colliderRect = collidable->rect();
		auto a = c;
		do {
			a = std::prev(a);
			auto active = *a;
			auto activeRect = active->rect();
			// if (activeRect.intersects(colliderRect)) {
			auto key = make_unordered_pair(collidable->id, active->id);
			if (compare(colliderRect, activeRect)){
				// auto key = make_unordered_pair(collidable->id, active->id);
				// colliders[key].pair = std::make_pair(collidable, active);
				// colliders[key].mask |= axis;
				// if (colliders[key].colliding()) {
				// 	activePairs.push_back(colliders[key].pair);
				// }
				addCollider(collidable, active, axis);
			}
			else {
				colliders[key].mask &= ~axis;
				// if (!colliders[key].colliding()) {
				// 	deactivePairs.push_back(colliders[key].pair);
				// }
			}
			if (little(colliderRect) > max) {
				break;
			}
		} while (a != collidables.begin());
		if (big(colliderRect) > max) {
			max = big(colliderRect);
		}
	}
}

void CollisionSystem::resolveCollisions() {
	wabi::insertion_sort<Collidable*>(sortedByX.begin(), sortedByX.end(), by_x);
	wabi::insertion_sort<Collidable*>(sortedByY.begin(), sortedByY.end(), by_y);
	// pairs.clear();
	previouslyActivePairs.clear();
	previouslyActivePairs.swap(activePairs);
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
	// for every pair we have determined is maybe colliding. Because type resolution is so hard we leave it to 
	// the class to determine if and how another object is truely colliding with it.
	for (auto&& pair : activePairs) {	
		EnterVisitor enter;
		StayVisitor stay;
		// if the collider was previously active
		auto search = std::find(previouslyActivePairs.begin(), previouslyActivePairs.end(), pair);
		if (search != previouslyActivePairs.end()) {		
			pair.first->accept(stay, pair.second);
			// Remove this pair from the previously colliding list so that when we're 
			// done all that is left is pairs that were colliding previously but are not anymore.
			previouslyActivePairs.remove(pair);
		}
		else{
			// otherwise the collider is freshly active
			pair.first->accept(enter, pair.second);
		}
	}
	// everyone left in the previouslyActive list is no longer colliding and should exit their collision;
	for (auto&& pair : previouslyActivePairs) {
		ExitVisitor exit;
		pair.first->accept(exit, pair.second);
	}

}

void CollisionSystem::clear() {
	sortedByX.clear();
	sortedByY.clear();
	colliders.clear();
}

size_t CollisionSystem::size() const {
	assert(sortedByX.size() == sortedByY.size());
	return sortedByX.size();
}

void CollisionSystem::addCollider(Collidable* c1, Collidable* c2, unsigned int axis) {
	auto key = make_unordered_pair(c1->id, c2->id);
	colliders[key].pair = std::make_pair(c1, c2);
	colliders[key].mask |= axis;
	if (colliders[key].colliding()) {
		activePairs.push_back(colliders[key].pair);
	}
	// All this loop search bullshit is cause std::find wasn't compiling and I'm in a hurry
	typedef std::list<std::pair<int, int>>::iterator fuckyou;
	auto find = []( fuckyou begin, fuckyou end, std::pair<int, int> key) -> bool {
	
		for (auto iter = begin; iter != end; std::advance(iter, 1)){
			if (*iter == key) {
				return true;
			}
		}
		return false;
	};
	std::list<std::pair<int, int>> c1IdList = key2Id[c1->id];
	std::list<std::pair<int, int>>  c2IdList = key2Id[c2->id];

	if (!find(c1IdList.begin(), c1IdList.end(), key)) {
		key2Id[c1->id].push_back(key);
	}
	if (!find(c2IdList.begin(), c2IdList.end(), key)) {
		key2Id[c2->id].push_back(key);
	}
}

// CollisionEnter
void EnterVisitor::visit(Collidable* c1, Collidable* c2) {
	c1->collisionEnter(c2);
}

void EnterVisitor::visit(PhysicsBody* pb, Collidable* c) {
	c->collisionEnter(pb);
}

void EnterVisitor::visit(Sea* sea, Collidable* c) {
	c->collisionEnter(sea);
}

void EnterVisitor::visit(Rock* rock, Collidable* c) {
	c->collisionEnter(rock);
}

void EnterVisitor::visit(Wave* wave, Collidable* c) {
	c->collisionEnter(wave);
}

void EnterVisitor::visit(Ship* ship, Collidable* c) {
	c->collisionEnter(ship);
}

//Collision Stay
void StayVisitor::visit(Collidable* c1, Collidable* c2) {
	c1->collisionStay(c2);
}

void StayVisitor::visit(PhysicsBody* pb, Collidable* c) {
	c->collisionStay(pb);
}

void StayVisitor::visit(Sea* sea, Collidable* c) {
	c->collisionStay(sea);
}

void StayVisitor::visit(Rock* rock, Collidable* c) {
	c->collisionStay(rock);
}

void StayVisitor::visit(Wave* wave, Collidable* c) {
	c->collisionStay(wave);
}

void StayVisitor::visit(Ship* ship, Collidable* c) {
	c->collisionStay(ship);
}

//Collision Stay
void ExitVisitor::visit(Collidable* c1, Collidable* c2) {
	c1->collisionExit(c2);
}

void ExitVisitor::visit(PhysicsBody* pb, Collidable* c) {
	c->collisionExit(pb);
}

void ExitVisitor::visit(Sea* sea, Collidable* c) {
	c->collisionExit(sea);
}

void ExitVisitor::visit(Rock* rock, Collidable* c) {
	c->collisionExit(rock);
}

void ExitVisitor::visit(Wave* wave, Collidable* c) {
	c->collisionExit(wave);
}

void ExitVisitor::visit(Ship* ship, Collidable* c) {
	c->collisionExit(ship);
}
