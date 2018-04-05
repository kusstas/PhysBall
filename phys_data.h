#ifndef PHYS_DATA_H
#define PHYS_DATA_H

#include "vector2.h"

struct PhysData
{
public:

    PhysData();

    const Vector2& getLocation() const;
    const Vector2& getVelocity() const;
    float getBounce() const;

    void setLocation(const Vector2& location);
    void setLocation(float x, float y);

    void setVelocity(const Vector2& velocity);
    void setVelocity(float x, float y);
    void setBounce(float bounce);

private:

    Vector2 location_;
    Vector2 velocity_;
    float bounce_;
};

#endif // PHYS_DATA_H
