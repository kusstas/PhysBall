#include "ball.h"

#include <QString>
#include <QInputDialog>
#include <QDebug>

Ball::Ball(QObject* parent) : QObject(parent)
{
    setVelocity(500, 500);
    setBounce(1.0f);
}

//---------------------------------------------------------

PhysData const& Ball::physData() const
{
    return m_physData;
}

QVector2D const& Ball::location() const
{
    return m_physData.location();
}

QVector2D const& Ball::velocity() const
{
    return m_physData.velocity();
}

float Ball::bounce() const
{
    return m_physData.bounce();
}

//---------------------------------------------------------

void Ball::setPhysData(PhysData const& physData)
{
    m_physData = physData;
}

void Ball::setLocation(QVector2D const& location)
{
    m_physData.setLocation(location);
}

void Ball::setLocation(float x, float y)
{
    m_physData.setLocation(x, y);
}

//---------------------------------------------------------

void Ball::setVelocity(const QVector2D& velocity)
{
    m_physData.setVelocity(velocity);
}

void Ball::setVelocity(float x, float y)
{
    m_physData.setVelocity(x, y);
}

//---------------------------------------------------------

void Ball::setBounce(float bounce)
{
    m_physData.setBounce(bounce);
}
