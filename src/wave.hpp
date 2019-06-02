
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
	Wave(Sea *sea, float x, float a);
	~Wave();

	float height(float x); // this can be a free function in the future, or a function pointer a caller provides	
	float slope(float x);
	float left();
	float right();

	void fixedUpdate();
	sf::Rect<float> rect();


	Sea *sea;
	sf::Vector2f position;
	float startX;
	float amplitude;
	float t = 0;
	float width = 0.01;
	float b = 0; // decay coefficient
	int id;
	

	static wabi::Time time;

private:
	static int _idSeed;

};

#endif // !WAVE_HPP
