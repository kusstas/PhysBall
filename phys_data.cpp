#include "phys_data.h"


PhysData::PhysData() : bounce_(1.0f)
{
}

//---------------------------------------------------------

const Vector2& PhysData::getLocation() const
{
    return location_;
}

const Vector2& PhysData::getVelocity() const
{
    return velocity_;
}

float PhysData::getBounce() const
{
    return bounce_;
}

//---------------------------------------------------------

void PhysData::setLocation(const Vector2& location)
{
    location_ = location;
}

void PhysData::setLocation(float x, float y)
{
    location_ = Vector2(x, y);
}

//---------------------------------------------------------

void PhysData::setVelocity(const Vector2& velocity)
{
    velocity_ = velocity;
}

void PhysData::setVelocity(float x, float y)
{
    velocity_ = Vector2(x, y);
}

void PhysData::setBounce(float bounce)
{
    if (bounce >= 0.0f)
        bounce_ = bounce;
}
