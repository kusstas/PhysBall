#ifndef BALL_H
#define BALL_H

#include <QObject>
#include "phys_data.h"

class Ball : public QObject
{
public:

    explicit Ball(QObject* parent = nullptr);

    const PhysData& getPhysData() const;

    const Vector2& getLocation() const;
    const Vector2& getVelocity() const;

    float getBounce() const;
    void setPhysData(const PhysData& physData);

    void setLocation(const Vector2& location);
    void setLocation(float x, float y);

    void setVelocity(const Vector2& velocity);
    void setVelocity(float x, float y);
    void setBounce(float bounce);

private:

    PhysData physData_;
};

#endif // BALL_H
