#include "renderer.h"
#include "render_worker.h"
#include "main_window.h"

#include <QThread>


Renderer::Renderer(MainWindow& drawWindow, QObject* parent) : QObject(parent)
{
    thread = new QThread();
    worker = new RenderWorker(*this);

    qRegisterMetaType<Vector2>("Vector2");

    connect(this, &Renderer::update, worker, RenderWorker::update, Qt::DirectConnection);
    connect(thread, &QThread::started, worker, &RenderWorker::work);
    connect(thread, &QThread::destroyed, worker, &RenderWorker::deleteLater);

    connect(worker, &RenderWorker::finished, thread, &QThread::quit);
    connect(worker, &RenderWorker::drawBall, &drawWindow, &MainWindow::drawBall, Qt::DirectConnection);

    worker->moveToThread(thread);
}

Renderer::~Renderer()
{
    thread->quit();
    thread->deleteLater();
}

//---------------------------------------------------------

void Renderer::start()
{
    thread->start();
}

//---------------------------------------------------------

void Renderer::newLocation(Vector2 location)
{
    emit update(location);
}
