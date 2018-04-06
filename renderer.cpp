#include "renderer.h"

Renderer::Renderer(QObject* parent) : QObject(parent), worker(*this)
{
    connect(this, &Renderer::update, &worker, RenderWorker::update, Qt::DirectConnection);
    connect(&thread, &QThread::started, &worker, &RenderWorker::work);
    connect(&worker, &RenderWorker::finished, &thread, &QThread::terminate);
    worker.moveToThread(&thread);
}

Renderer::~Renderer()
{
    thread.terminate();
}

//---------------------------------------------------------

void Renderer::start()
{
    thread.start();
}

void Renderer::setSize(const Vector2& size)
{
    this->size = size;
}

//---------------------------------------------------------

void Renderer::newLocation(Vector2 location)
{
    emit update(location);
}
