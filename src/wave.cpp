#include <iostream>
#include <limits>

#include "game.hpp"
#include "sea.hpp"
#include "ship.hpp"
#include "utils.hpp"
#include "visitor.hpp"
#include "wave.hpp"

// statics

Wave::Wave(Game *g, float x, float a) : startX(x), amplitude(a)
{
    game = g;
    position = sf::Vector2f(x, game->sea->level);
}

Wave::~Wave() {}

void Wave::accept(Visitor &v) { return v.visit(this); }

void Wave::accept(CollisionVisitor &v, Collidable *c) { v.visit(this, c); }

float Wave::height(float x) const
{
    // cool guassian
    return amplitude * decay * std::pow(M_E, -std::pow(width * (x - position.x), 2));
}

float Wave::overlapingHeight(float x) const
{
    auto h = 0;
    for (auto &&w : overlapingWaves)
    {
        h += w->height(x);
    }
    return h;
}

float Wave::totalHeight(float x) const
{
    return height(x) + overlapingHeight(x);
}

float Wave::maxHeight() const
{
    auto max = 0.f;
    for (float i = left(); i < right(); i += 0.5)
    {
        max = std::max(max, totalHeight(i));
    }
    return max;
}

float Wave::slope(float x) const
{
    // derivative of height
    return height(x) * (-2 * width * (x - position.x) * width);
}

void Wave::update(const float deltaTime)
{
    // time += deltaTime * 100;
    time += deltaTime * 10;
    addForce(sf::Vector2f(time, 0));
    addForce(dragForce(0.1225f));
    if (decay >= 1.f)
    {
        sign = -0.25f;
    }
    else if (decay <= 0.f && sign <= 0)
    {
        sign = 0;
        decay = 0;
        active = false;
    }
    decay = decay + sign * deltaTime;
    // width = width + sign * deltaTime;
    PhysicsBody::update(deltaTime);
}

float Wave::left() const
{
    return position.x - 2.5f * (1 / width);
}

float Wave::right() const
{
    return position.x + 2.5f * (1 / width);
}

wabi::Rectf Wave::rect() const
{
    // float h = height(position.x);
    float h = maxHeight();
    float top = position.y + h;
    return wabi::Rectf(left(), top, right() - left(), h);
}

void Wave::collisionEnter(Wave *wave)
{
    overlapingWaves.push_back(wave);
}

void Wave::collisionExit(Wave *wave)
{
    overlapingWaves.remove(wave);
}

void Wave::collisionEnter(Ship *ship)
{
    ship->collisionEnter(this);
}

void Wave::collisionStay(Ship *ship)
{
    ship->collisionStay(this);
}
