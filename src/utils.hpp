#ifndef UTILS_HPP
#define UTILS_HPP

#define _USE_MATH_DEFINES

#include <cmath>
#include <math.h>
#include <random>
#include <chrono>
#include <functional>
#include <chrono>
#include <SFML/Graphics.hpp>


extern int SCREEN_HEIGHT;
extern int SCREEN_WIDTH;
// extern std::chrono::duration<float> deltaTime; // just make sure you call keepTime everyframe


namespace wabi
{

	typedef std::chrono::time_point<std::chrono::system_clock> timepoint;
	typedef std::chrono::duration<float> duration;

	class Time {
	public:
		static duration deltaTime;
		static duration totalTime;
		static timepoint start;
		static timepoint end;

		Time() { }
		void keepTime();
		void reset();
		
	};

	// inline timepoint keepTime(timepoint start) {
	// 	// this must be inline because deltaTime is externally defined (this should probably be wrapped in a static class
	// 	auto end = std::chrono::system_clock::now();
	// 	deltaTime = end - start;
	// 	return end;
	// }
	

	template <typename T>
	T randomNumber(T start, T end)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<T> dist(start, end);
		return (T)dist(gen);
	}

	template <typename T, typename Iter, typename Pred>
	void insertion_sort(Iter begin, Iter end, Pred predicate) {
		for (auto it = begin; it != end; ++it) {
			std::rotate(std::upper_bound(begin, it, *it, predicate), it, std::next(it)); 
		}
	}

	template <typename T, typename Pred>
	typename std::vector<T>::iterator insert_sorted(std::vector<T> &v, T item, Pred predicate) {
		return v.insert(
			std::upper_bound(v.begin(), v.end(), item, predicate),
			item
		);
	}


	template <typename T>
	T squareMagnitude(const sf::Vector2<T> &v)
	{
		return v.x * v.x + v.y * v.y;
	}
	
	template <typename T>
	T magnitude(const sf::Vector2<T> &v)
	{
	    return sqrt(squareMagnitude(v));
	}
	
	template <typename T>
	sf::Vector2<T> normalized(sf::Vector2<T> v)
	{
	    T mag = magnitude<T>(v);
	    return sf::Vector2<T>(
	        static_cast<T>(v.x / mag),
	        static_cast<T>(v.y / mag));
	}
	
	template <typename T>
	sf::Vector2<T> randomVector2()
	{
		return sf::Vector2<T>(randomNumber<T>(static_cast<T>(0), static_cast<T>(SCREEN_WIDTH)),
			randomNumber<T>(static_cast<T>(0), static_cast<T>(SCREEN_HEIGHT)));
	}
	
	template <typename T>
	sf::Vector2<T> randomVector2(T start, T end)
	{
	    auto blah{std::bind(randomNumber<T>, start, end)};
	    return sf::Vector2<T>(blah(), blah());
	}	

	template <typename T>
	sf::Vector2<T> brainToScreenSpace(const sf::Vector2<T> in) {
		return sf::Vector2<T>(in.x, (SCREEN_HEIGHT - in.y));
	}

	template <typename T>
	sf::Vector2<T> screenToBrainSpace(const sf::Vector2<T> in) {
		return sf::Vector2<T>(in.x, abs(SCREEN_HEIGHT - in.y));
	}

} // namespace wabi

template <typename T>
std::ostream &operator<<(std::ostream &os, const sf::Vector3<T> &v)
{
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}



template <typename T>
std::ostream &operator<<(std::ostream &os, const sf::Vector2<T> &v)
{
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}


#endif // !UTILS_HPP
