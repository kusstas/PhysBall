#include "phys_worker.h"

#include "phys_engine.h"
#include "ball.h"

#include <QThread>

PhysWorker::PhysWorker(PhysEngine& owner, Ball& ball, QObject *parent) : QObject(parent)
{
    this->owner = &owner;
    this->ball = &ball;

    isWork = false;
}

//---------------------------------------------------------

void PhysWorker::work()
{
    isWork = true;
    emit started();
    while(isWork)
    {
        if (ball != nullptr)
        {
            const PhysData& pd = ball->getPhysData();
            PhysData new_pd = compute(pd, owner->getVectorG(),
                                      owner->getTimeScale() * PhysEngine::ms_period * 0.001f);
            emit resultReady(new_pd);
        }
        QThread::msleep(PhysEngine::ms_period);
    }
    emit finished();
}

void PhysWorker::stop()
{
    isWork = false;
}

//---------------------------------------------------------

PhysData PhysWorker::compute(const PhysData& physData, const Vector2& vectorG, float time)
{
    PhysData pd;
    pd.setBounce(physData.getBounce());
    Vector2 loc = physData.getLocation();
    Vector2 v = physData.getVelocity();

    v += vectorG * time;
    loc += v * time;

    if (loc.x < owner->getLeftWall())
    {
        loc.x = owner->getLeftWall();
        v.x *= -pd.getBounce();
    }
    else if (loc.x > owner->getRightWall())
    {
        loc.x = owner->getRightWall();
        v.x *= -pd.getBounce();
    }

    if (loc.y > owner->getTopWall())
    {
        loc.y = owner->getTopWall();
        v.y *= -pd.getBounce();
    }
    else if (loc.y < owner->getBottomWall())
    {
        loc.y = owner->getBottomWall();
        v.y *= -pd.getBounce();
    }


    pd.setLocation(loc);
    pd.setVelocity(v);
    return pd;
}
