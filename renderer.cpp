#include "renderer.h"
#include <QThread>

#include "main_window.h"

Renderer::Renderer(MainWindow& drawWindow, QObject* parent) : QObject(parent), worker(*this)
{
    thread = new QThread();

    qRegisterMetaType<Vector2>("Vector2");
    connect(this, &Renderer::update, &worker, RenderWorker::update, Qt::DirectConnection);
    connect(thread, &QThread::started, &worker, &RenderWorker::work);
    connect(&worker, &RenderWorker::finished, thread, &QThread::quit);
    connect(&worker, &RenderWorker::drawBall, &drawWindow, &MainWindow::drawBall, Qt::DirectConnection);

    worker.moveToThread(thread);
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

void Renderer::setSize(const Vector2& size)
{
    this->size = size;
}

//---------------------------------------------------------

void Renderer::newLocation(Vector2 location)
{
    emit update(location);
}
