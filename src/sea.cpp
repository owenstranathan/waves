
#include <cassert>
#include <limits>

#include "sea.hpp"
#include "ship.hpp"
#include "game.hpp"
#include "wave.hpp"
#include "rock.hpp"
#include "utils.hpp"
#include "visitor.hpp"

Sea::Sea(Game* g, float l) : game(g), level(l) {}

Sea::~Sea() { }

void Sea::accept(Visitor& v) { return v.visit(this); }

void Sea::accept(CollisionVisitor& v, Collidable* c) { v.visit(this, c); }


void Sea::update(const wabi::duration& ) { }

float Sea::slope(float x) const {
	float m = 0;
	for (auto&& w : game->waves) {
		m += w->slope(x);
	}
	return m;
}

float Sea::height(float x) const {
	float h = level;
	for (auto && w : game->waves) {
		h += w->height(x);
	}
	return h;
}

wabi::Rectf Sea::rect() const {
	float max = level;
	for (auto&& w : game->waves) {
		max = std::max(max, level + w->height(w->position.x));
	}
	return wabi::Rectf(0.f, level, game->worldWidth, FLT_MAX/2); 
}

void Sea::resolveCollision(Rock* rock) {
	rock->resolveCollision(this);
}

void Sea::resolveCollision(Ship* ship) {
	ship->resolveCollision(this);
}

