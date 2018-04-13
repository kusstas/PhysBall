#ifndef PHYS_ENGINE_H
#define PHYS_ENGINE_H

#include <QObject>

#include "phys_worker.h"
#include "phys_data.h"

class Ball;

class PhysEngine : public QObject
{
    Q_OBJECT

public:

    explicit PhysEngine(Ball& ball, QObject* parent = nullptr);
    virtual ~PhysEngine();

    static const int ms_period = 1;

    void start();

    float getTimeScale() const;
    const Vector2& getVectorG() const;

    float getTopWall() const;
    float getLeftWall() const;
    float getBottomWall() const;
    float getRightWall() const;

    void setTimeScale(float scale);
    void setVectorG(const Vector2& vectorG);

    void setTopWall(float yLine);
    void setLeftWall(float xLine);
    void setBottomWall(float yLine);
    void setRightWall(float xLine);

signals:

    void started();

    void newLocation(Vector2 vector2);

public slots:

    void resultReady(PhysData physData);

private:

    Ball* ball;
    QThread* thread;
    PhysWorker worker;

    float topWall;
    float leftWall;
    float bottomWall;
    float rightWall;

    float timeScale;
    Vector2 vectorG;

};

#endif // PHYS_ENGINE_H
