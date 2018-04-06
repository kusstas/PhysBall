#include "render_worker.h"

#include <QThread>

#include <QDebug>


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
        qDebug() << t.x << " " << t.y;
        QThread::msleep(500);
    }
    emit finished();
}

void RenderWorker::stop()
{
    isWork = false;
}

void RenderWorker::update(Vector2 location)
{
    t = location;
}
