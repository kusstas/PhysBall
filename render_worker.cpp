#include "render_worker.h"
#include "renderer.h"

#include <QThread>

RenderWorker::RenderWorker(Renderer& owner, QObject* parent) : QObject(parent)
{
    this->owner = &owner;
    isWork = false;
}

void RenderWorker::work()
{
    isWork = true;
    while(isWork)
    {
        emit drawBall(locationBall);
        QThread::msleep(Renderer::ms_period);
    }
    emit finished();
}

void RenderWorker::stop()
{
    isWork = false;
}

void RenderWorker::update(Vector2 location)
{
    locationBall = location;
}
