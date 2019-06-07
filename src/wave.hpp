
#ifndef WAVE_HPP
#define WAVE_HPP


#include <vector>
#include <math.h>

#include "prelude.hpp"
#include "utils.hpp"
#include "collidable.hpp"

// TODO: make a wave management class (ObjectPool)

class Wave : public Collidable {
public:
	Wave(Sea *sea, float x, float a);
	~Wave();

	float height(float x) const; 
	float slope(float x) const;
	float left() const;
	float right() const;

	virtual void accept(Visitor &);
	virtual void update(wabi::duration deltaTime);
	virtual sf::Rect<float> rect() const;


	Sea *sea;
	sf::Vector2f position;
	float startX;
	float amplitude;
	float t = 0;
	float width = 0.01;
	float b = 0; // decay coefficient
	int id;
	
private:
	static int _idSeed;

};

#endif // !WAVE_HPP
