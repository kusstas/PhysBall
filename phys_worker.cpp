#include "phys_worker.h"
#include "phys_engine.h"
#include "ball.h"

PhysWorker::PhysWorker(PhysEngine& owner, Ball& ball, QObject *parent) : QObject(parent)
{
    this->owner = &owner;
    this->ball = &ball;

    isWork = false;
}

//---------------------------------------------------------

void PhysWorker::work()
{
    const float t_scale = 0.002f;
    isWork = true;
    emit started();
    while(isWork)
    {
        if (ball != nullptr)
        {
            const PhysData& pd = ball->getPhysData();
            PhysData new_pd = compute(pd, owner->getVectorG(), owner->getTimeScale() * t_scale);
            emit resultReady(new_pd);
        }
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
    Vector2 loc = physData.getLocation();
    Vector2 v = physData.getVelocity();

    v += vectorG * time;
    loc += v * time;

    if (loc.x < owner->getLeftWall())
    {
        loc.x = owner->getLeftWall();
        v.x *= -physData.getBounce();
    }
    else if (loc.x > owner->getRightWall())
    {
        loc.x = owner->getRightWall();
        v.x *= -physData.getBounce();
    }

    if (loc.y > owner->getTopWall())
    {
        loc.y = owner->getTopWall();
        v.y *= -physData.getBounce();
    }
    else if (loc.y < owner->getBottomWall())
    {
        loc.y = owner->getBottomWall();
        v.y *= -physData.getBounce();
    }

    pd.setLocation(loc);
    pd.setVelocity(v);
    return pd;
}
