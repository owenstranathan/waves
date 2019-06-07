#pragma once

#include <list>

#include "prelude.hpp"
#include "utils.hpp"
#include "collidable.hpp"


class Sea : public Collidable{
public:
	Sea(float l);
	~Sea();

	virtual void accept(Visitor&);
	virtual void update(wabi::duration deltaTime);
	Wave * createWave(float position, float magnitude);
	void cleanUpWaves();
	float height(float x) const;
	float slope(float x) const;
	sf::Rect<float> rect() const;

	std::list<Wave*> waves;
	float level;
};


