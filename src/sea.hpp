#ifndef SEA_HPP
#define SEA_HPP

// #include "everybodyinthepool.hpp"
#include "utils.hpp"
#include "wave.hpp"

class Wave; 

class Sea {
public:
	Sea();

	void createWave(float position, float magnitude);
	void fixedUpdate();
	Wave* waveAtX(float x);

	float level;
// private:
	std::vector<Wave*> waves;
};

#endif // !SEA_HPP
