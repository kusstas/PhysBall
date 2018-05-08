#include "render_worker.h"
#include <QThread>

RenderWorker::RenderWorker(QObject* parent) : QObject(parent)
{
    setPeriodMs(24);

    m_isWork = false;
    m_isShouldWork = false;
}

//---------------------------------------------------------

void RenderWorker::doWork()
{
    m_isShouldWork = true;
    m_isWork = true;

    emit started();
    while(m_isShouldWork) {
        emit draw(m_location);
        QThread::msleep(periodMs());
    }
    m_isWork = false;
    emit finished();
}

void RenderWorker::stop()
{
    m_isShouldWork = false;
}

void RenderWorker::updateLocation(QVector2D const& location)
{
    m_location = location;
}

//---------------------------------------------------------

bool RenderWorker::isWork() const
{
    return m_isWork;
}

long RenderWorker::periodMs() const
{
    return m_periodMs;
}

void RenderWorker::setPeriodMs(long periodMs)
{
    Q_ASSERT(periodMs > 0);
    m_periodMs = periodMs;
}
