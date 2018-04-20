#include "render_worker.h"
#include <QThread>

RenderWorker::RenderWorker(QObject* parent) : QObject(parent)
{
    setPeriodMs(20);

    isWork_ = false;
    isShouldWork_ = false;
}

//---------------------------------------------------------

void RenderWorker::doWork()
{
    isShouldWork_ = true;
    isWork_ = true;

    emit started();
    while(isShouldWork_)
    {
        emit draw(location_);
        QThread::msleep(periodMs());
    }
    isWork_ = false;
    emit finished();
}

void RenderWorker::stop()
{
    isShouldWork_ = false;
}

void RenderWorker::updateLocation(QVector2D location)
{
    location_ = location;
}

//---------------------------------------------------------

bool RenderWorker::isWork() const
{
    return isWork_;
}

long RenderWorker::periodMs() const
{
    return periodMs_;
}

void RenderWorker::setPeriodMs(long periodMs)
{
    Q_ASSERT(periodMs > 0);
    periodMs_ = periodMs;
}
