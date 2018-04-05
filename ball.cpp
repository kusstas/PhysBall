#include "ball.h"

Ball::Ball(QObject* parent) : QObject(parent)
{
}

//---------------------------------------------------------

const PhysData& Ball::getPhysData() const
{
    return physData_;
}

const Vector2& Ball::getLocation() const
{
    return physData_.getLocation();
}

const Vector2& Ball::getVelocity() const
{
    return physData_.getVelocity();
}

float Ball::getBounce() const
{
    return physData_.getBounce();
}

//---------------------------------------------------------

void Ball::setPhysData(const PhysData& physData)
{
    physData_ = physData;
}

void Ball::setLocation(const Vector2& location)
{
    physData_.setLocation(location);
}

void Ball::setLocation(float x, float y)
{
    physData_.setLocation(x, y);
}

//---------------------------------------------------------

void Ball::setVelocity(const Vector2& velocity)
{
    physData_.setVelocity(velocity);
}

void Ball::setVelocity(float x, float y)
{
    physData_.setVelocity(x, y);
}

//---------------------------------------------------------

void Ball::setBounce(float bounce)
{
    physData_.setBounce(bounce);
}
