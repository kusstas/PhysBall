#ifndef BALL_H
#define BALL_H

#include <QObject>
#include "phys_data.h"

class Ball : public QObject
{
public:

    explicit Ball(QObject* parent = nullptr);
    virtual ~Ball();

    const PhysData& physData() const;

    const QVector2D& location() const;
    const QVector2D& velocity() const;

    float bounce() const;

    void setPhysData(const PhysData& physData);

    void setLocation(const QVector2D& location);
    void setLocation(float x, float y);

    void setVelocity(const QVector2D& velocity);
    void setVelocity(float x, float y);
    void setBounce(float bounce);

private:

    PhysData physData_;
};

#endif // BALL_H
