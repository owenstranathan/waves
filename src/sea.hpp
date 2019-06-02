#ifndef SEA_HPP
#define SEA_HPP

// #include "everybodyinthepool.hpp"
#include <list>

#include "utils.hpp"
#include "wave.hpp"

class Wave; 

// TODO: make the sea a wave pool. (i.e. cache wave instances on creation and clean up)
class Sea {
public:
	Sea();
	~Sea();

	void createWave(float position, float magnitude);
	void cleanUpWaves();
	void fixedUpdate();
	float height(float x);
	float slope(float x);

	float level;
// private:
	std::list<Wave*> waves;
};


#endif // !SEA_HPP
