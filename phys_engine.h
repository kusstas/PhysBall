#ifndef PHYS_ENGINE_H
#define PHYS_ENGINE_H

#include <QObject>

struct Vector2;
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

    void finished();

public slots:

    //void createdBall(Ball& ball);

private:

    Ball* ball;

    float topWall;
    float leftWall;
    float bottomWall;
    float rightWall;

};

#endif // PHYS_ENGINE_H
