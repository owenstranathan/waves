
#include <iostream>

#include "utils.hpp"
#include "wave.hpp"


float Wave::height(float x) {
	// e^{-0.05t^2}sin(pi * x)\ 
	float returnValue = 0.0f;
	for (auto&& f : components) {
		returnValue += f(x, *this);
	}
	return returnValue;
	// return magnitude * std::pow(M_E, -0.05 * time * time) * std::pow(std::sinf((1.0f/magnitude) * M_PI * x - time), 2);
}

void Wave::updateVertices(){
	for (float x = 0; x < SCREEN_WIDTH; x += (SCREEN_WIDTH/size)) {
		int index = (x*size) / SCREEN_WIDTH;
		// vertices[index] = transform.transformPoint(sf::Vector2f(x, height(x)));
		vertices[index] = sf::Vector2f(x, height(x));
	}
}

void Wave::fixedUpdate() {
	updateVertices();
	wabi::Time t;
	time += t.deltaTime.count();
	// if (time < 0) {
	//  	time += t.deltaTime.count() * 20;
	// }
	// else {
	//  	time += t.deltaTime.count();
	// }
	//transform.translate(1, 1);
	// transform.translate(5.0f, 0);
}
