#pragma once

#include "utils.hpp"
#include "prelude.hpp"
#include "physicsbody.hpp"

class Platform : public PhysicsBody
{
public:
    // Platform() {}
    Platform(float h, float w) : height(h), width(w) {}
    virtual ~Platform() {}

    float height;
    float width;
};
