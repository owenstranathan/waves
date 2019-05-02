#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "utils.hpp"
#include "wave.hpp"
#include "rock.hpp"

sf::RenderTarget& operator<<(sf::RenderTarget &rt,  Wave& wave);  // draw a wave on a RenderTarget
sf::RenderTarget& operator<<(sf::RenderTarget &rt, Rock& rock);   // draw a rock on a RenderTarget

#endif // !GRAPHICS_HPP
