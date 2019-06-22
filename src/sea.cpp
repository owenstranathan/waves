
#include <cassert>
#include "sea.hpp"
#include "game.hpp"
#include "wave.hpp"
#include "rock.hpp"
#include "utils.hpp"
#include "visitor.hpp"

Sea::Sea(Game* g, float l) : game(g), level(l) {}

Sea::~Sea() { }

void * Sea::accept(Visitor& v) { return v.visit(this); }

void* Sea::resolveCollision(Collidable*) { return nullptr; }

void* Sea::resolveCollision(Rock* rock) {
	return rock->resolveCollision(this);
}

void Sea::update(wabi::duration deltaTime) { }

float Sea::slope(float x) const {
	float m = 0;
	for (auto&& w : game->waves) {
		m += w->slope(x);
	}
	return m;
}

float Sea::height(float x) const {
	float h = level;
	// for (auto&& w : wavesAtX(x)) {
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
	return wabi::Rectf(0.f, max, SCREEN_WIDTH, max);
}
