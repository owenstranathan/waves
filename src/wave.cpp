#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>

#include "wave.hpp"


float Wave::height(float x) {
	// e^{-0.05t^2}sin(pi * x)\ 
	return magnitude * std::pow(M_E, -0.05 * time * time) * std::pow(std::sinf((1.0f/magnitude) * M_PI * x), 2);
}

void Wave::updateVertices(){
	for (float x = 0; x < magnitude; x += (magnitude/size)) {
		int index = (x*size) / magnitude;
		vertices[index].x = x;
		vertices[index].y = height(x);
	}
}

sf::Vector2f Wave::max() {
	return sf::Vector2f();
}

void Wave::draw(sf::RenderTarget & rt) {
	sf::CircleShape point(3);
	point.setFillColor(sf::Color::Black);
	// std::transform(verts.begin(), verts.end(), [this](sf::Vector2f p) -> sf::Vector2f { return transform.transformPoint(p); });
	for (int i = 0; i < size; i++) {
		// sf::Vector2f newPos = transform.transformPoint(vertices[i]);
		// point.setPosition(newPos);

		point.setPosition(wabi::brainToScreenSpace(transform.transformPoint(vertices[i])));
		rt.draw(point);
	}
}

void Wave::fixedUpdate() {
	updateVertices();
	time += deltaTime.count() * 5;
	if (time < 0) {
	 	time += deltaTime.count() * 5;
	}
	else {
	 	time += deltaTime.count() * 5;
	}
	//transform.translate(1, 1);
	transform.translate(5, 0);
}
