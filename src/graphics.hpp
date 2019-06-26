#pragma once

#include "utils.hpp"
#include "prelude.hpp"

#define SEA_COLOR sf::Color::Cyan

class Graphics {
public:

	Graphics(Game *, sf::RenderTarget*, sf::VideoMode&);
	~Graphics();

	void draw() const;
	void draw(const CollisionSystem&) const;
	void draw(const Sea&) const;
	void draw(const Rock&) const;
	void draw(const Ship&) const;
	void draw(const Collidable&, sf::Color) const;

	template <typename T>
	void draw(const wabi::Rect<T>& rect, sf::Color color) const;

	template <typename T>
	void draw(const sf::Rect<T>& rect, sf::Color color) const;

	template<typename T>
	static sf::Vector2<T> game2ScreenPos(const sf::Vector2<T>& v);

	template<typename T>	
	static sf::Vector2<T> screen2GamePos(const sf::Vector2<T> & v);

	template<typename T>
	static sf::Rect<T> game2ScreenRect(const wabi::Rect<T>& in);

	static float pixelsPerUnit;
	static int SCREEN_HEIGHT;
	static int SCREEN_WIDTH;
	sf::Font* const font;
	sf::Text* const text;
	Game* const game;
	sf::RenderTarget* target;

};

template<typename T>
sf::Vector2<T> Graphics::game2ScreenPos(const sf::Vector2<T>& v) {
	return sf::Vector2<T>(v.x * pixelsPerUnit, SCREEN_HEIGHT-(v.y * pixelsPerUnit));
}

template<typename T>
sf::Vector2<T> Graphics::screen2GamePos(const sf::Vector2<T>& v) {
	return sf::Vector2<T>(v.x, std::abs(SCREEN_HEIGHT - v.y)) / (T)(pixelsPerUnit);
}
	
template<typename T>
sf::Rect<T> Graphics::game2ScreenRect(const wabi::Rect<T>& in) {
	return sf::Rect<T>(game2ScreenPos(sf::Vector2<T>(in.left, in.top)), sf::Vector2<T>(in.width * pixelsPerUnit, in.height * pixelsPerUnit));
}

/*
We want the game to use actual real world numbers for our physics calculations.
So we are going to make our unit a meter. So if something has a scalar value of one for a
size they you can assume that it would map to 1m in reality.

1st Assertion:
	1 gu(game unit) = 1 m(meter)

Since we are using a semi-arbitrary unit mapping we need to scale our units out to appropriate 
pixel values.
For example if we have a 5gu x 6gu ship then we can't just draw a 5x6 pixel blob. It'll just look like a dot.
So we need a consistent transformation ration between world units and pixels.

for now, fuck it. Lets call it 15 pixels per game unit (meters) ( px / gu(m) ). 
*/

