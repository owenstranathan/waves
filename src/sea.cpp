
#include <cassert>

#include "sea.hpp"
#include "wave.hpp"
#include "utils.hpp"
#include "visitor.hpp"

Sea::Sea(float l) : level(l) {}

Sea::~Sea() {
	for (auto&& w : waves) {
		delete w;
	}
}

void Sea::accept(Visitor& v) { v.visit(this); }

Wave* Sea::createWave(float position, float magnitude) {
	Wave * wave = new Wave(this, position, magnitude);
	wabi::insert_sorted(waves, wave, [](Wave * a, Wave * b)->bool {return a->rect().left < b->rect().left; });
	return wave;
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

void Sea::update(wabi::duration deltaTime) {
	for (auto&& w : waves)
		w->update(deltaTime);
	cleanUpWaves();
}

float Sea::slope(float x) const {
	float m = 0;
	for (auto&& w : waves) {
		m += w->slope(x);
	}
	return m;
}

float Sea::height(float x) const {
	float h = level;
	// for (auto&& w : wavesAtX(x)) {
	for (auto && w : waves) {
		h += w->height(x);
	}
	return h;
}

sf::Rect<float> Sea::rect() const {
	return sf::FloatRect(0.f, level, SCREEN_WIDTH, level);
}

