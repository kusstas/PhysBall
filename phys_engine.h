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
    const QVector2D& vectorG() const;

    float topWall() const;
    float leftWall() const;
    float bottomWall() const;
    float rightWall() const;

    void setTimeScale(float scale);
    void setVectorG(const QVector2D& vectorG_);

    void setTopWall(float yLine);
    void setLeftWall(float xLine);
    void setBottomWall(float yLine);
    void setRightWall(float xLine);

signals:

    void started();
    void finished();
    void updateLocation(QVector2D vector2);

public slots:

    void start();
    void stop();

private slots:

    void resultReady(PhysData physData);

private:

    Ball& ball_;

    QThread thread_;
    PhysWorker worker_;

    float topWall_;
    float leftWall_;
    float bottomWall_;
    float rightWall_;

    float timeScale_;
    QVector2D vectorG_;

};



#endif // PHYS_ENGINE_H
