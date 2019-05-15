
#ifndef WAVE_HPP
#define WAVE_HPP


#include <vector>
#include <math.h>

// #include "everybodyinthepool.hpp"
#include "utils.hpp"
#include "collidable.hpp"
#include "sea.hpp"


class Sea;

// return wave->magnitude* std::pow(M_E, -0.05 * wave->time * wave->time) * std::pow(std::sinf((1.0f / wave->magnitude) * M_PI * x - wave->time), 2);
class Wave : Collidable {
public:
	Wave(Sea const* sea, float position, float magnitude, float time=0);
	~Wave();

	float height(float x); // this can be a free function in the future, or a function pointer a caller provides	
	void updateVertices();
	void fixedUpdate();
	sf::Rect<float> rect();
	float tomd();

	Sea const * sea;
	sf::Vector2f position; 
	float t;
	float magnitude;
	float dc = -0.05; // decay coefficient

	static wabi::Time time;

};

#endif // !WAVE_HPP
