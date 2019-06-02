
#include <iostream>

#include "utils.hpp"
#include "wave.hpp"
#include "sea.hpp"

// statics
wabi::Time Wave::time = wabi::Time();
int Wave::_idSeed = 0;

Wave::Wave(Sea * s, float x, float a) : sea(s), startX(x), amplitude(a), id(++_idSeed), position(x, sea->level) {}
Wave::~Wave() { }

float Wave::height(float x) {
	// cool guassian
	return amplitude * b * std::pow(M_E, - std::pow(width * (x - position.x), 2));
}

float Wave::slope(float x) {
	// derivative of height
	return height(x) * (-2 * width * (x - position.x) * width);
}

void Wave::fixedUpdate() {
	static float sign = 5.f;
	auto dt = time.deltaTime.count();
	t += dt * 50;
	position.x = startX + t;
	if (b >= 1.f) {
		sign = -0.5f;
	} else if (b <= 0.f && sign <= 0) {
		sign = 0;
		b = 0;
	}
	b = b + sign * dt;
}

float Wave::left() {
	return position.x - 2.5f * (1 / width);
}

float Wave::right() {
	return position.x + 2.5f * (1 / width);
}

sf::Rect<float> Wave::rect() {
	float h = height(position.x);
	float top = position.y + h;
	return sf::Rect<float>(left(), top, right() - left(), h);
}



