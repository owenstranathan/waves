#pragma once

#include <vector>
#include <math.h>

#include "collidable.hpp"
#include "physicsbody.hpp"
#include "prelude.hpp"
#include "utils.hpp"

// TODO: make a wave management class (ObjectPool)

class Wave : public PhysicsBody
{
public:
    Wave(Game *, float, float);
    virtual ~Wave();

    float height(float x) const;
    float overlapingHeight(float x) const;
    float totalHeight(float x) const;
    float maxHeight() const;
    float slope(float x) const;
    float left() const;
    float right() const;

    virtual void accept(Visitor &) override;
    virtual void collisionEnter(Wave *) override;
    virtual void collisionExit(Wave *) override;
    virtual void collisionEnter(Ship *) override;
    virtual void collisionStay(Ship *) override;

    virtual void accept(CollisionVisitor &, Collidable *c) override;
    virtual void update(const float) override;
    virtual wabi::Rectf rect() const override;

    float startX;
    float amplitude;
    float sign = 5.f;
    float time = 0;
    float width = 0.1;
    float decay = 0;
    std::list<Wave *> overlapingWaves;

private:
    float _do_maxHeight(float left, float right);
};
