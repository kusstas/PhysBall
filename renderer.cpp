#include "renderer.h"

Renderer::Renderer(QObject* parent) : QObject(parent)
{
    connect(&thread_, &QThread::started, &worker_, &RenderWorker::doWork);
    connect(this, &Renderer::updateLocation, &worker_, &RenderWorker::updateLocation, Qt::DirectConnection);
    connect(&worker_, &RenderWorker::started, this, &Renderer::started);
    connect(&worker_, &RenderWorker::draw, this, &Renderer::draw, Qt::DirectConnection);
    connect(&worker_, &RenderWorker::finished, this, &Renderer::finished, Qt::DirectConnection);
    connect(&worker_, &RenderWorker::finished, &thread_, &QThread::quit, Qt::DirectConnection);

    worker_.moveToThread(&thread_);
}

//---------------------------------------------------------

bool Renderer::isWork() const
{
    return worker_.isWork();
}

//---------------------------------------------------------

void Renderer::start()
{
    thread_.start();
}

void Renderer::stop()
{
    worker_.stop();
    thread_.wait();
}
