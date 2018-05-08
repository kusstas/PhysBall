#ifndef PHYS_ENGINE_H
#define PHYS_ENGINE_H

#include <QObject>
#include <QThread>

#include "phys_worker.h"

class Ball;

class PhysEngine : public QObject
{
    Q_OBJECT

public:

    explicit PhysEngine(Ball& ball, QObject* parent = nullptr);

    bool isWork() const;

    float timeScale() const;
    QVector2D const& vectorG() const;

    float topWall() const;
    float leftWall() const;
    float bottomWall() const;
    float rightWall() const;

    void setTimeScale(float scale);
    void setVectorG(QVector2D const& m_vectorG);

    void setTopWall(float yLine);
    void setLeftWall(float xLine);
    void setBottomWall(float yLine);
    void setRightWall(float xLine);

signals:

    void started();
    void finished();
    void updateLocation(QVector2D const& vector2);
    void updatePhysData(PhysData const& data);

public slots:

    void start();
    void stop();

private slots:

    void resultReady(PhysData const& physData);

private:

    Ball& m_ball;

    QThread m_thread;
    PhysWorker m_worker;

    float m_topWall;
    float m_leftWall;
    float m_bottomWall;
    float m_rightWall;

    float m_timeScale;
    QVector2D m_vectorG;

};



#endif // PHYS_ENGINE_H
