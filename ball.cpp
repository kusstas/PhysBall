#include "ball.h"

#include <QString>
#include <QInputDialog>

Ball::Ball(QObject* parent) : QObject(parent)
{
    setVelocity(600, 700);
    setBounce(1.0f);

    QString nickName;
    while(nickName.isEmpty()) {
        nickName = QInputDialog::getText(nullptr, "Input dialog", "Enter nickname: ");
    }
}

Ball::~Ball()
{
}

//---------------------------------------------------------

const PhysData& Ball::physData() const
{
    return physData_;
}

const QVector2D& Ball::location() const
{
    return physData_.location();
}

const QVector2D& Ball::velocity() const
{
    return physData_.velocity();
}

float Ball::bounce() const
{
    return physData_.bounce();
}

//---------------------------------------------------------

void Ball::setPhysData(const PhysData& physData)
{
    physData_ = physData;
}

void Ball::setLocation(const QVector2D& location)
{
    physData_.setLocation(location);
}

void Ball::setLocation(float x, float y)
{
    physData_.setLocation(x, y);
}

//---------------------------------------------------------

void Ball::setVelocity(const QVector2D& velocity)
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
