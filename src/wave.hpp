#ifndef WAVE_HPP
#define WAVE_HPP


#include <cmath>
#include <vector>
#include "utils.hpp"

class Wave;

class WavyBoy {
private:
	WavyBoy() {}
public:
	WavyBoy(Wave * wave) : wave(wave) {}
	~WavyBoy() {}
	
	virtual float operator()(float) = 0;

	Wave* wave;
	
};

class WavyBoyNaught : public WavyBoy {
	float operator()(float x) { return 10; };
};

class WavyBoyDefault : public WavyBoy {
	float operator()(float x) {
		return wave->magnitude* std::pow(M_E, -0.05 * wave->time * wave->time) * std::pow(std::sinf((1.0f / wave->magnitude) * M_PI * x - wave->time), 2);
	}
};

class Wave {
public:
	Wave(float m, float s = 10) : magnitude(m), size(s), time(-12), transform(), vertices(new sf::Vector2f[size]), components({ WavyBoyNaught(this) }) {}

	~Wave() {
		delete[] vertices;
	}

	float height(float x); // this can be a free function in the future, or a function pointer a caller provides	
	void updateVertices();
	void draw(sf::RenderTarget & rt);
	void fixedUpdate();

	sf::Transform transform;
	sf::Vector2f position;
	float time;
	float size;
	float magnitude;
	sf::Vector2f * vertices;
	std::vector<WavyBoy> components;
};

#endif // !WAVE_HPP
