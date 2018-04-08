#include "ball.h"

#include <QTextStream>
#include <QFile>

Ball::Ball(QObject* parent) : QObject(parent)
{
    bool isReaded = readPhysData();
    if (!isReaded)
    {
        setVelocity(400, 200);
        setBounce(0.95f);
    }
}

Ball::~Ball()
{
    writePhysData();
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

//---------------------------------------------------------

bool Ball::readPhysData()
{
    QFile file(fileSave);

    bool isOpen = file.open(QFile::ReadOnly | QFile::Text);
    if (isOpen)
    {
        QTextStream in(&file);
        in >> physData_;
    }

    file.close();
    return isOpen;
}

void Ball::writePhysData()
{
    QFile file(fileSave);

    bool isOpen = file.open(QFile::WriteOnly | QFile::Text);
    if (isOpen)
    {
        QTextStream out(&file);
        out << physData_;
    }
    file.flush();
    file.close();
}
