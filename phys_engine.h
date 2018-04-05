#ifndef PHYS_ENGINE_H
#define PHYS_ENGINE_H

#include <QObject>
#include "phys_data.h"

class Ball;

class PhysEngine : public QObject
{
    Q_OBJECT

public:

    explicit PhysEngine(QObject* parrent = nullptr);

    void setTopWall(float yLine);
    void setLeftWall(float xLine);
    void setBottomWall(float yLine);
    void setRightWall(float xLine);

signals:

    void newLocation(const Vector2& vector2);

public slots:

    void createdBall(Ball& ball);

private:

    Ball* ball;

    float topWall;
    float leftWall;
    float bottomWall;
    float rightWall;

    PhysData compute(const PhysData& physData, const Vector2& vectorG, float time);

};

#endif // PHYS_ENGINE_H
