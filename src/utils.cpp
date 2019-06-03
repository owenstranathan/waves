#include "utils.hpp"

namespace wabi {

	// statics
	duration Time::deltaTime = duration(0);
	duration Time::totalTime = duration(0);
	timepoint Time::start = timepoint();
	timepoint Time::end = timepoint();


	void Time::keepTime() {
		if (start == timepoint())
			start = end = std::chrono::system_clock::now();
		else
			end = std::chrono::system_clock::now();
		deltaTime = end - start;
		start = end;
		totalTime += deltaTime;
	}


	void Time::reset() {
		totalTime = duration(0);
	}
}