#include "phys_worker.h"
#include "phys_engine.h"

#include <QThread>

PhysWorker::PhysWorker(PhysEngine& owner, PhysData const& physData, QObject* parent)
    : QObject(parent), m_owner(owner), m_physData(physData)
{
    setPeriodMs(10);

    m_isWork = false;
    m_isShouldWork = false;
}

//---------------------------------------------------------

void PhysWorker::doWork()
{
    m_isShouldWork = true;
    m_isWork = true;

    emit started();
    while(m_isShouldWork) {
        float time = m_owner.timeScale() * periodMs() / 1000;
        PhysData new_pd = compute(m_physData, m_owner.vectorG(), time);
        emit resultReady(new_pd);
        QThread::msleep(periodMs());
    }
    m_isWork = false;
    emit finished();
}

void PhysWorker::stop()
{
    m_isShouldWork = false;
}

//---------------------------------------------------------

bool PhysWorker::isWork() const
{
    return m_isWork;
}

long PhysWorker::periodMs() const
{
    return m_periodMs;
}

void PhysWorker::setPeriodMs(long periodMs)
{
    Q_ASSERT(periodMs > 0);
    m_periodMs = periodMs;
}

//---------------------------------------------------------

PhysData PhysWorker::compute(PhysData const& physData, QVector2D const& vectorG, float time)
{
    PhysData pd;
    pd.setBounce(physData.bounce());
    QVector2D loc = physData.location();
    QVector2D v = physData.velocity();

    v += vectorG * time;
    loc += v * time;

    if (loc.x() < m_owner.leftWall()) {
        loc.setX(m_owner.leftWall());
        v.setX(v.x() * -pd.bounce());
    }
    else if (loc.x() > m_owner.rightWall()) {
        loc.setX(m_owner.rightWall());
        v.setX(v.x() * -pd.bounce());
    }

    if (loc.y() > m_owner.topWall()) {
        loc.setY(m_owner.topWall());
        v.setY(v.y() * -pd.bounce());
    }
    else if (loc.y() < m_owner.bottomWall()) {
        loc.setY(m_owner.bottomWall());
        v.setY(v.y() * -pd.bounce());;
    }


    pd.setLocation(loc);
    pd.setVelocity(v);
    return pd;
}
