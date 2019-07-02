
#include <cassert>
#include <limits>

#include "sea.hpp"
#include "ship.hpp"
#include "game.hpp"
#include "wave.hpp"
#include "rock.hpp"
#include "utils.hpp"
#include "visitor.hpp"

Sea::Sea(Game *g, float l) : game(g), level(l) {}

Sea::~Sea() {}

void Sea::accept(Visitor &v) { return v.visit(this); }

void Sea::accept(CollisionVisitor &v, Collidable *c) { v.visit(this, c); }

void Sea::update(const float) {}

float Sea::slope(float x) const
{
    float m = 0;
    for (auto &&w : game->waves)
    {
        m += w->slope(x);
    }
    return m;
}

float Sea::height(float x) const
{
    float h = level;
    for (auto &&w : game->waves)
    {
        h += w->height(x);
    }
    return h;
}

wabi::Rectf Sea::rect() const
{
    float max = level;
    for (auto &&w : game->waves)
    {
        max = std::max(max, level + w->height(w->position.x));
    }
    // return wabi::Rectf(0.f, level, game->worldWidth, FLT_MAX/2); // I guess FLT_MAX isn't
    // defined on all platforms
    return wabi::Rectf(0.f, level, game->worldWidth, std::numeric_limits<float>::max() / 2);
    // return wabi::Rectf(0.f, max, game->worldWidth, std::numeric_limits<float>::max() / 2);
}

void Sea::collisionEnter(Rock *rock)
{
    rock->collisionEnter(this);
}

void Sea::collisionStay(Rock *rock)
{
    rock->collisionStay(this);
}

void Sea::collisionEnter(Ship *ship)
{
    ship->collisionEnter(this);
}

void Sea::collisionStay(Ship *ship)
{
    ship->collisionStay(this);
}
