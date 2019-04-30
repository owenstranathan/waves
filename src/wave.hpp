#ifndef WAVE_HPP
#define WAVE_HPP


#include <cmath>
#include <vector>
#include "utils.hpp"


class Wave {
public:
	Wave(float m, float s = 10) :magnitude(m), size(s), time(-12), transform(), vertices(new sf::Vector2f[size]) { }

	~Wave() {
		delete[] vertices;
	}

	float height(float x); // this can be a free function in the future, or a function pointer a caller provides	
	void updateVertices();
	void draw(sf::RenderTarget & rt);
	void fixedUpdate();
	sf::Vector2f max();

	sf::Transform transform;
	sf::Vector2f position;
	float time;
	float size;
	float magnitude;
	sf::Vector2f * vertices;
};

#endif // !WAVE_HPP
