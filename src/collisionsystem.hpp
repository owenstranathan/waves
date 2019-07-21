#pragma once

#include <unordered_map>
#include <set>

#include "utils.hpp"
#include "prelude.hpp"
#include "visitor.hpp"

const unsigned int X_AXIS = 1 << 0; // 1 (0001)
const unsigned int Y_AXIS = 1 << 1; // 2 (0010)

template <typename T, typename U, typename O>
std::pair<T, U> make_ordered_pair(T t, U u, O orderby)
{
	if (orderby(t) < orderby(u))
	{
		return std::make_pair(t, u);
	}
	else
	{
		return std::make_pair(u, t);
	}
	// return std::make_pair(std::min(unaryPred(t), unaryPred(u)), std::max(unaryPred(t), unaryPred(u)));
}

struct PairHash
{
	template <typename T, typename U>
	size_t operator()(const std::pair<T, U> &pair) const
	{
		auto h1 = std::hash<T>{}(std::min(pair.first, pair.second)); // get the std::hash for the smallest in the pair
		auto h2 = std::hash<U>{}(std::max(pair.first, pair.second)); // get the std::hash for the largest in the pair
		return h1 ^ h2;												 // return the XOR of the 2 hashes (which I guess is unique)
	}
};

struct Collider
{
	std::pair<Collidable *, Collidable *> pair;
	unsigned int mask;

	bool colliding()
	{
		return static_cast<bool>(mask & Y_AXIS) && static_cast<bool>(mask & X_AXIS);
	}
};

class CollisionSystem
{
public:
	CollisionSystem(Game *);

	void addCollidable(Collidable *);
	void removeCollidable(Collidable *);
	void resolveCollisions();
	void sweepAxis(unsigned int,
				   std::list<Collidable *> &,
				   std::function<bool(wabi::Rectf, wabi::Rectf)>,
				   std::function<float(wabi::Rectf)>,
				   std::function<float(wabi::Rectf)>);
	void activateColliderForAxis(Collidable *c1, Collidable *c2, unsigned int axis);
	void clear();
	size_t size() const;
	inline const std::list<Collidable *> collidables() const
	{
		return sortedByX;
	}

	std::unordered_map<std::pair<int, int>, Collider, PairHash> colliders;
	std::unordered_map<int, std::list<std::pair<int, int>>> key2Id;
	std::list<std::pair<Collidable *, Collidable *>> activePairs;
	std::list<std::pair<Collidable *, Collidable *>> previouslyActivePairs;
	std::list<Collidable *> sortedByX;
	std::list<Collidable *> sortedByY;
	// std::set<std::pair<int, int>> seenKeys;
	Game *game;
};

class CollisionVisitor
{
public:
	virtual void visit(Collidable *, Collidable *){};
	virtual void visit(PhysicsBody *, Collidable *){};
	virtual void visit(Sea *, Collidable *){};
	virtual void visit(Wave *, Collidable *){};
	virtual void visit(Rock *, Collidable *){};
	virtual void visit(Ship *, Collidable *){};
	virtual void visit(Platform *, Collidable *){};
};

class EnterVisitor : public CollisionVisitor
{
public:
	virtual void visit(Collidable *, Collidable *) override;
	virtual void visit(PhysicsBody *, Collidable *) override;
	virtual void visit(Sea *, Collidable *) override;
	virtual void visit(Wave *, Collidable *) override;
	virtual void visit(Rock *, Collidable *) override;
	virtual void visit(Ship *, Collidable *) override;
	virtual void visit(Platform *, Collidable *) override;
};

class ExitVisitor : public CollisionVisitor
{
public:
	virtual void visit(Collidable *, Collidable *) override;
	virtual void visit(PhysicsBody *, Collidable *) override;
	virtual void visit(Sea *, Collidable *) override;
	virtual void visit(Wave *, Collidable *) override;
	virtual void visit(Rock *, Collidable *) override;
	virtual void visit(Ship *, Collidable *) override;
	virtual void visit(Platform *, Collidable *) override;
};

class StayVisitor : public CollisionVisitor
{
public:
	virtual void visit(Collidable *, Collidable *) override;
	virtual void visit(PhysicsBody *, Collidable *) override;
	virtual void visit(Sea *, Collidable *) override;
	virtual void visit(Wave *, Collidable *) override;
	virtual void visit(Rock *, Collidable *) override;
	virtual void visit(Ship *, Collidable *) override;
	virtual void visit(Platform *, Collidable *) override;
};
