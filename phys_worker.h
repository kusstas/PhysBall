#ifndef PHYS_WORKER_H
#define PHYS_WORKER_H

#include <QObject>
#include "phys_data.h"

class Ball;
class PhysEngine;

class PhysWorker : public QObject
{
    Q_OBJECT

public:

    explicit PhysWorker(PhysEngine& owner, Ball& ball, QObject *parent = nullptr);

signals:

    void started();
    void finished();

    void resultReady(PhysData physData);

public slots:

    void work();
    void stop();

private:

    bool isWork;

    PhysEngine* owner;
    Ball* ball;

    PhysData compute(const PhysData& physData, const Vector2& vectorG, float time);

};

#endif // PHYS_WORKER_H
