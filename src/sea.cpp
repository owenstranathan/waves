
#include <cassert>

#include "sea.hpp"
#include "wave.hpp"
#include "utils.hpp"

Sea::Sea() : level(200), waves() {}

Sea::~Sea() {
	for (auto&& w : waves) {
		delete w;
	}
}

void Sea::createWave(float position, float magnitude) {
	Wave * wave = new Wave(this, position, magnitude);
	wabi::insert_sorted(waves, wave, [](Wave * a, Wave * b)->bool {return a->rect().left < b->rect().left; });
}


void Sea::cleanUpWaves() {
	std::list<Wave*> remove;
	for (auto&& wave : waves) {
		if (wave->b == 0)
			remove.push_back(wave);
	}
	for (auto && wave : remove){
		// auto it = std::find(waves.begin(), waves.end(), wave);
		waves.remove(wave);
		delete wave;
	}
}

void Sea::fixedUpdate() {
	for (auto&& w : waves)
		w->fixedUpdate();
	cleanUpWaves();
}

float Sea::slope(float x) {
	float m = 0;
	for (auto&& w : waves) {
		m += w->slope(x);
	}
	return m;
}

float Sea::height(float x) {
	float h = level;
	// for (auto&& w : wavesAtX(x)) {
	for (auto && w : waves) {
		h += w->height(x);
	}
	return h;
}
