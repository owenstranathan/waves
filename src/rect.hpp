#pragma once
#include <SFML/Graphics.hpp>

namespace wabi {
	template <typename T>
	class Rect {
	public:
		Rect();
		Rect(T rectLeft, T rectTop, T rectWidth, T rectHeight);
		Rect(const sf::Vector2<T>& position, const sf::Vector2<T>& size);
		template <typename U>
		explicit Rect(const Rect<U>& rectangle);
		T right() const;
		T bottom() const;
		bool intersects(const Rect<T>&) const;
		bool intersects(const Rect<T>&, Rect<T>&) const;
		sf::Vector2<T> min() const;
		sf::Vector2<T> max() const;

		T left;   ///< Left coordinate of the rectangle
		T top;    ///< Top coordinate of the rectangle
		T width;  ///< Width of the rectangle
		T height; ///< Height of the rectangle

	};

	template <typename T>
	Rect<T>::Rect() : left(0), top(0), width(0), height(0) {}

	template <typename T>
	Rect<T>::Rect(T l, T t, T w, T h) : left(l), top(t), width(w), height(h) { }

	template <typename T>
	Rect<T>::Rect(const sf::Vector2<T>& position, const sf::Vector2<T>& size) : left(position.x), top(position.y), width(size.x), height(size.y) {}

	template <typename T>
	template <typename U>
	Rect<T>::Rect(const Rect<U>& r) : left(r.left), top(r.top), width(r.width), height(r.height) { }


	template <typename T>
	T Rect<T>::right() const {
		return left + width;
	}

	template <typename T>
	T Rect<T>::bottom() const {
		return top - height;
	}

	template <typename T>
	bool Rect<T>::intersects(const Rect<T>& rectangle) const {
		Rect<T> intersection;
		return intersects(rectangle, intersection);
	}

	template <typename T>
	bool Rect<T>::intersects(const Rect<T>& rectangle, Rect<T>& intersection) const {  
		// Straight up copied this from sf::Rect 
		// I just need this to function in my special space. I think maybe inverting the world is not worth the effort

		// Rectangles with negative dimensions are allowed, so we must handle them correctly

		// Compute the min and max of the first rectangle on both axes
		T r1MinX = std::min(left, right());
		T r1MaxX = std::max(left, right());
		T r1MinY = std::min(top, bottom());
		T r1MaxY = std::max(top, bottom());

		// Compute the min and max of the second rectangle on both axes
		T r2MinX = std::min(rectangle.left, rectangle.right());
		T r2MaxX = std::max(rectangle.left, rectangle.right());
		T r2MinY = std::min(rectangle.top, rectangle.bottom());
		T r2MaxY = std::max(rectangle.top, rectangle.bottom());

		// Compute the intersection boundaries
		T interLeft   = std::max(r1MinX, r2MinX);
		T interTop    = std::max(r1MinY, r2MinY);
		T interRight  = std::min(r1MaxX, r2MaxX);
		T interBottom = std::min(r1MaxY, r2MaxY);

		// If the intersection is valid (positive non zero area), then there is an intersection
		if ((interLeft < interRight) && (interTop < interBottom))
		{	    
			intersection = Rect<T>(interLeft, interTop, interRight - interLeft, interBottom - interTop);
		    return true;
		}
		else
		{
		    intersection = Rect<T>(0, 0, 0, 0);
		    return false;
		}

	}

	template<typename T>
	sf::Vector2<T> Rect<T>::min() const {
		return sf::Vector2<T>(left, top);
	}

	template<typename T>
	sf::Vector2<T> Rect<T>::max() const {
		return sf::Vector2<T>(right(), bottom());
	}

	typedef Rect<float> Rectf;
	typedef Rect<int> Recti;
	typedef Rect<double> Rectd;
}

