#ifndef BALL_H
#define BALL_H

#include "phys_data.h"

class Ball
{
public:

    Ball();
    Ball(float radius);
    Ball(Vector2 location, float radius);

    const PhysData& getPhysData() const;

    const Vector2& getLocation() const;
    const Vector2& getVelocity() const;

    float getRadius() const;
    float getBounce() const;

    void setPhysData(const PhysData& physData);

    void setLocation(const Vector2& location);
    void setLocation(float x, float y);

    void setVelocity(const Vector2& velocity);
    void setVelocity(float x, float y);

    void setRadius(float radius);
    void setBounce(float bounce);

private:

    PhysData physData_;
    float radius_;
};

#endif // BALL_H
