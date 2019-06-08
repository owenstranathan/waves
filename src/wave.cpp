#include <iostream>
#include "utils.hpp"
#include "visitor.hpp"
#include "wave.hpp"
#include "game.hpp"
#include "sea.hpp"

// statics
int Wave::_idSeed = 0;

Wave::Wave(Game * g, float x, float a) : game(g), startX(x), amplitude(a), id(++_idSeed), position(x, game->sea->level) {}

Wave::~Wave() { }

void* Wave::resolveCollision(Collidable*) {
	return nullptr;
}

void * Wave::accept(Visitor& v) { return v.visit(this); }

float Wave::height(float x) const {
	// cool guassian
	return amplitude * decay * std::pow(M_E, - std::pow(width * (x - position.x), 2));
}

float Wave::slope(float x) const {
	// derivative of height
	return height(x) * (-2 * width * (x - position.x) * width);
}

void Wave::update(wabi::duration deltaTime) {
	auto dt = deltaTime.count();
	time += dt * 100;
	position.x = startX + time;
	if (decay >= 1.f) {
		sign = -0.5f;
	} else if (decay <= 0.f && sign <= 0) {
		sign = 0;
		decay = 0;
		active = false;
	}
	decay = decay + sign * dt;
}

float Wave::left() const {
	return position.x - 2.5f * (1 / width);
}

float Wave::right() const {
	return position.x + 2.5f * (1 / width);
}

sf::Rect<float> Wave::rect() const {
	float h = height(position.x);
	float top = position.y + h;
	return sf::Rect<float>(left(), top, right() - left(), h);
}

