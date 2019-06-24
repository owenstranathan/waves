# pragma once

#include <unordered_map>

#include "utils.hpp"
#include "prelude.hpp"
#include "visitor.hpp"


const unsigned int X_AXIS = 1 << 0; // 1 (0001)
const unsigned int Y_AXIS = 1 << 1; // 2 (0010)

template <typename T, typename U>
std::pair<T, U> make_unordered_pair(T t, U u) {
	return std::make_pair(std::min(t, u), std::max(t, u));
}

struct PairHash {
	template <typename T, typename U>
	size_t operator()(const std::pair<T, U>& pair) const {
		auto h1 = std::hash<T>{}(std::min(pair.first, pair.second)); // get the std::hash for the smallest in the pair
		auto h2 = std::hash<U>{}(std::max(pair.first, pair.second)); // get the std::hash for the largest in the pair
		return h1 ^ h2; // return the XOR of the 2 hashes (which I guess is unique)
	}
};


struct Collider {
	std::pair<Collidable*, Collidable*> pair;
	unsigned int mask;

	bool colliding() {
		return static_cast<bool>(mask & Y_AXIS) && static_cast<bool>(mask & X_AXIS);
	}
};

class CollisionSystem {
public:
	CollisionSystem(Game*);

	void resolveCollisions();
	void SweepAxis(unsigned int, 
		std::list<Collidable*>&,
		std::function<bool(wabi::Rectf, wabi::Rectf)>,
		std::function<float(wabi::Rectf)>, 
		std::function<float(wabi::Rectf)>);
	void addCollider(Collidable*);
	void removeCollider(Collidable*);
	void clear();
	size_t size() const;
	inline const std::list<Collidable*> colliders() const {
		return sortedByX;
	}
	
	// std::list<Collidable*> colliders;
	std::unordered_map<std::pair<int, int>, Collider, PairHash> pairs;
	std::list<std::pair<Collidable*, Collidable*>> activePairs;
	std::list<Collidable*> sortedByX;
	std::list<Collidable*> sortedByY;
	Game* game;
};


class CollisionVisitor {
public:
	virtual void visit(Collidable*, Collidable*);
	virtual void visit(PhysicsBody*, Collidable*);
	virtual void visit(Sea*, Collidable*);
	virtual void visit(Wave*, Collidable*);
	virtual void visit(Rock*, Collidable*);
	virtual void visit(Ship*, Collidable*);
};
