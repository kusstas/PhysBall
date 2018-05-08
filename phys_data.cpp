#include "phys_data.h"

PhysData::PhysData() : m_bounce(1.0f)
{
}

//---------------------------------------------------------

QVector2D const& PhysData::location() const
{
    return m_location;
}

QVector2D const& PhysData::velocity() const
{
    return m_velocity;
}

float PhysData::bounce() const
{
    return m_bounce;
}

//---------------------------------------------------------

void PhysData::setLocation(QVector2D const& location)
{
    m_location = location;
}

void PhysData::setLocation(float x, float y)
{
    m_location = QVector2D(x, y);
}

//---------------------------------------------------------

void PhysData::setVelocity(const QVector2D& velocity)
{
    m_velocity = velocity;
}

void PhysData::setVelocity(float x, float y)
{
    m_velocity = QVector2D(x, y);
}

void PhysData::setBounce(float bounce)
{
    if (bounce >= 0.0f)
    {
        m_bounce = bounce;
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
