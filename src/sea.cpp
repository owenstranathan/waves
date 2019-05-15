#include "sea.hpp"
#include "wave.hpp"
#include "utils.hpp"

Sea::Sea() : level(200), waves() {}

void Sea::createWave(float position, float magnitude) {
	Wave * wave = new Wave(this, position, magnitude);
	wabi::insert_sorted(waves, wave, [](Wave * a, Wave * b)->bool {return a->rect().left < b->rect().left; });
}

void Sea::fixedUpdate() {
	for (auto&& w : waves)
		w->fixedUpdate();
}

Wave* Sea::waveAtX(float x){
	for (auto&& w : waves) {
		auto r = w->rect();
		if (r.left <= x && (r.left + r.width) >= x)
			return w;
	}
	return nullptr;
}