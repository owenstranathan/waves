#define _USE_MATH_DEFINES

#include <cmath>

#include "wave.hpp"

float Wave::height(float x) {
	return std::pow(M_E, std::pow(-0.05 * t, 2))* std::sinf(M_PI * x);
}

std::vector<sf::Vector2f> Wave::verticies(){
	std::vector<sf::Vector2f> ret;
	for (float x = 0; x < 1; x += .001f) {
		ret.push_back(transform.transformPoint(sf::Vector2f(x, height(x))));
	}
	return ret;
}

void Wave::draw(sf::RenderTarget & rt) {
	sf::CircleShape point(1);
	point.setFillColor(sf::Color::Black);
	auto verts = verticies();
	point.setPosition(*verts.begin());
	rt.draw(point);
	for (auto p = std::next(verts.begin()); p != verts.end(); p++) {
		point.setPosition(*p);
		rt.draw(point);
	}
}
