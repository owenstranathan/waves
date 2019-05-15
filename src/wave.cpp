
#include <iostream>

#include "utils.hpp"
#include "wave.hpp"
#include "sea.hpp"

// statics
wabi::Time Wave::time = wabi::Time();

Wave::Wave(Sea const * s, float p, float m, float time) : sea(s), position(p, sea->level), magnitude(m), t(time) { }

Wave::~Wave() { }

float Wave::height(float x) {
	// float mag_recip = 1.0f / magnitude;
	// return (magnitude/ ( time + 1)) * std::pow(M_E, -1.0f * std::pow(mag_recip * x - time, 2)) + 200; 
	// return magnitude * std::pow(M_E, (-1.0f / (magnitude*magnitude)) * std::pow(x - time, 2)) + 200; 

	return magnitude * std::pow(M_E, dc * t * t) * std::pow(std::sinf((1.0f / magnitude) * M_PI * x), 2) + sea->level;
}

void Wave::updateVertices(){
	// float step = magnitude / num_vertices;
	// auto r = rect();
	// for (float x = 0; x < magnitude; x += step) {
	// 	int index = (x * num_vertices) / magnitude;
	// 	vertices[index] = sf::Vector2f(x + r.left, height(x)+sea->level);
	// }
}

void Wave::fixedUpdate() {
	// updateVertices();
	t += time.deltaTime.count();
	position.x += time.deltaTime.count() * 50;
	// if (time < 0) {
	//  	time += t.deltaTime.count() * 20;
	// }
	// else {
	//  	time += t.deltaTime.count();
	// }
	//transform.translate(1, 1);
	// transform.translate(5.0f, 0);
}

sf::Rect<float> Wave::rect() {
	float left = position.x - magnitude;
	float h = height(position.x);
	float top = position.y + h;
	return sf::Rect<float>(left, top, magnitude, h);
}

float Wave::tomd() { // time of maximal decay
	// t = sqrt((1/decayCoeff)*ln(ALMOST_ZERO))
	return std::sqrt((1.0f / dc) * std::logf(ALMOST_ZERO));
}

