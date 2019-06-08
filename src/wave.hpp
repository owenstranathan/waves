
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
	Wave(Game*, float, float);
	~Wave();

	float height(float x) const; 
	float slope(float x) const;
	float left() const;
	float right() const;

	virtual void* resolveCollision(Collidable*);
	virtual void * accept(Visitor &);
	virtual void update(wabi::duration deltaTime);
	virtual sf::Rect<float> rect() const;


	// Sea *sea;
	Game* game;
	sf::Vector2f position;
	float startX;
	float amplitude;
	float sign = 5.f;
	float time = 0;
	float width = 0.01;
	float decay = 0; // decay coefficient
	int id;
	
private:
	static int _idSeed;

};

#endif // !WAVE_HPP
