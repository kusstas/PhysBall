#ifndef BALL_H
#define BALL_H

#include <QObject>
#include "phys_data.h"

class Ball : public QObject
{
public:

    explicit Ball(QObject* parent = nullptr);

    PhysData const& physData() const;

    QVector2D const& location() const;
    QVector2D const& velocity() const;

    float bounce() const;

    void setPhysData(PhysData const& physData);

    void setLocation(QVector2D const& location);
    void setLocation(float x, float y);

    void setVelocity(QVector2D const& velocity);
    void setVelocity(float x, float y);
    void setBounce(float bounce);

private:

    PhysData m_physData;
};

#endif // BALL_H
