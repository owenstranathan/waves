#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "utils.hpp"
#include "wave.hpp"
#include "rock.hpp"
#include "sea.hpp"

const sf::Color SeaColor = sf::Color::Blue;
const sf::Color WaveColor = SeaColor;

sf::RenderTarget& operator<<(sf::RenderTarget &rt, Sea& sea);   // draw a sea on a RenderTarget
sf::RenderTarget& operator<<(sf::RenderTarget &rt,  Wave& wave);  // draw a wave on a RenderTarget
sf::RenderTarget& operator<<(sf::RenderTarget &rt, Rock& rock);   // draw a rock on a RenderTarget

#endif // !GRAPHICS_HPP
