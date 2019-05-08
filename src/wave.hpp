
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
	Wave(Sea const * s, float p, float m, float t = 0, float n = 100) 
		: sea(s), position(p, sea->level), magnitude(m),  num_vertices(n), t(t), vertices(new sf::Vector2f[num_vertices]){ }

	~Wave() {
		delete[] vertices;
	}

	float height(float x); // this can be a free function in the future, or a function pointer a caller provides	
	void updateVertices();
	void fixedUpdate();
	sf::Rect<float> rect();
	float tomd();

	Sea const * sea;
	sf::Vector2f position; 
	float t;
	float num_vertices;
	float magnitude;
	float dc = -0.05; // decay coefficient
	sf::Vector2f * vertices;

	static wabi::Time time;

};

#endif // !WAVE_HPP
