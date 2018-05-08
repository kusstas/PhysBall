#include "renderer.h"

#include <QDebug>

Renderer::Renderer(QObject* parent) : QObject(parent)
{
    connect(&m_thread, &QThread::started, &m_worker, &RenderWorker::doWork);
    connect(this, &Renderer::updateLocation, &m_worker, &RenderWorker::updateLocation, Qt::DirectConnection);
    connect(&m_worker, &RenderWorker::started, this, &Renderer::started);
    connect(&m_worker, &RenderWorker::draw, this, &Renderer::draw, Qt::DirectConnection);
    connect(&m_worker, &RenderWorker::finished, this, &Renderer::finished);
    connect(&m_worker, &RenderWorker::finished, &m_thread, &QThread::quit, Qt::DirectConnection);

    // Log connect
    connect(&m_worker, &RenderWorker::started, []() { qDebug() << "Renderer: started"; });
    connect(&m_worker, &RenderWorker::finished, []() { qDebug() << "Renderer: finished"; });

    m_worker.moveToThread(&m_thread);
}

//---------------------------------------------------------

bool Renderer::isWork() const
{
    return m_worker.isWork();
}

//---------------------------------------------------------

void Renderer::start()
{
    m_thread.start();
}

void Renderer::stop()
{
    m_worker.stop();
    m_thread.wait();
}
