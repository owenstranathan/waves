#ifndef SEA_HPP
#define SEA_HPP

// #include "everybodyinthepool.hpp"
#include "utils.hpp"
#include "wave.hpp"

class Wave; 

class Sea {
public:
	Sea() : level(200), waves() {

	}

	float level;
	std::vector<Wave*> waves;
};

#endif // !SEA_HPP
