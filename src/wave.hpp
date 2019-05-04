
#ifndef WAVE_HPP
#define WAVE_HPP


#include <vector>
#include "utils.hpp"
#include <math.h>



// return wave->magnitude* std::pow(M_E, -0.05 * wave->time * wave->time) * std::pow(std::sinf((1.0f / wave->magnitude) * M_PI * x - wave->time), 2);
class Wave {
public:
	Wave(float m,float s = 10) : magnitude(m),  size(s), time(-12), transform(), vertices(new sf::Vector2f[size]){ }

	~Wave() {
		delete[] vertices;
	}

	float height(float x); // this can be a free function in the future, or a function pointer a caller provides	
	void updateVertices();
	void fixedUpdate();

	sf::Transform transform;
	sf::Vector2f position;
	float time;
	float size;
	float magnitude;
	sf::Vector2f * vertices;
	// std::vector<std::function<float(float, Wave&)>> components;
};

#endif // !WAVE_HPP
