#ifndef BALL_H
#define BALL_H

#include <QObject>
#include <QString>

#include "phys_data.h"

class Ball : public QObject
{
public:

    explicit Ball(QObject* parent = nullptr);
    virtual ~Ball();

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

    const QString fileSave = "fileSave.txt";
    PhysData physData_;

    bool readPhysData();
    void writePhysData();

};

#endif // BALL_H
