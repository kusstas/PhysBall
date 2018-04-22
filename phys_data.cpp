#include "phys_data.h"

PhysData::PhysData() : bounce_(1.0f)
{
}

//---------------------------------------------------------

const QVector2D& PhysData::location() const
{
    return location_;
}

const QVector2D& PhysData::velocity() const
{
    return velocity_;
}

float PhysData::bounce() const
{
    return bounce_;
}

//---------------------------------------------------------

void PhysData::setLocation(const QVector2D& location)
{
    location_ = location;
}

void PhysData::setLocation(float x, float y)
{
    location_ = QVector2D(x, y);
}

//---------------------------------------------------------

void PhysData::setVelocity(const QVector2D& velocity)
{
    velocity_ = velocity;
}

void PhysData::setVelocity(float x, float y)
{
    velocity_ = QVector2D(x, y);
}

void PhysData::setBounce(float bounce)
{
    if (bounce >= 0.0f)
    {
        bounce_ = bounce;
    }
}

//---------------------------------------------------------

QString PhysData::toString() const
{
    QString format = "location x:%1 y:%2; velocity x:%3 y:%4; bounce %5;";
    return format.arg(location().x()).arg(location().y()).
            arg(velocity().x()).arg(velocity().y()).
            arg(bounce());
}
