#include "phys_worker.h"
#include "phys_engine.h"

#include <QThread>

PhysWorker::PhysWorker(PhysEngine& owner, const PhysData& physData, QObject* parent)
    : QObject(parent), owner_(owner), physData_(physData)
{
    setPeriodMs(10);

    isWork_ = false;
    isShouldWork_ = false;
}

//---------------------------------------------------------

void PhysWorker::doWork()
{
    isShouldWork_ = true;
    isWork_ = true;

    emit started();
    while(isShouldWork_)
    {
        float time = owner_.timeScale() * periodMs() / 1000;
        PhysData new_pd = compute(physData_, owner_.vectorG(), time);
        emit resultReady(new_pd);
        QThread::msleep(periodMs());
    }
    isWork_ = false;
    emit finished();
}

void PhysWorker::stop()
{
    isShouldWork_ = false;
}

//---------------------------------------------------------

bool PhysWorker::isWork() const
{
    return isWork_;
}

long PhysWorker::periodMs() const
{
    return periodMs_;
}

void PhysWorker::setPeriodMs(long periodMs)
{
    Q_ASSERT(periodMs > 0);
    periodMs_ = periodMs;
}

//---------------------------------------------------------

PhysData PhysWorker::compute(const PhysData& physData, const QVector2D& vectorG, float time)
{
    PhysData pd;
    pd.setBounce(physData.bounce());
    QVector2D loc = physData.location();
    QVector2D v = physData.velocity();

    v += vectorG * time;
    loc += v * time;

    if (loc.x() < owner_.leftWall())
    {
        loc.setX(owner_.leftWall());
        v.setX(v.x() * -pd.bounce());
    }
    else if (loc.x() > owner_.rightWall())
    {
        loc.setX(owner_.rightWall());
        v.setX(v.x() * -pd.bounce());
    }

    if (loc.y() > owner_.topWall())
    {
        loc.setY(owner_.topWall());
        v.setY(v.y() * -pd.bounce());
    }
    else if (loc.y() < owner_.bottomWall())
    {
        loc.setY(owner_.bottomWall());
        v.setY(v.y() * -pd.bounce());;
    }


    pd.setLocation(loc);
    pd.setVelocity(v);
    return pd;
}
