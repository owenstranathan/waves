#ifndef WAVE_HPP
#define WAVE_HPP


#include <cmath>
#include <vector>
#include "utils.hpp"


class Wave {
public:
	Wave() : t(0) {}
	Wave(int time) : t(time), transform() {}
	Wave(float time) : t(time), transform() {}

	float height(float x); // this can be a free function in the future, or a function pointer a caller provides
	std::vector<sf::Vector2f> verticies();
	void draw(sf::RenderTarget & rt);

	sf::Transform transform;
	float t;
};

#endif // !WAVE_HPP
