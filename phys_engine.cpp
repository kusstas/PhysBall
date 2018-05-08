#include "phys_engine.h"
#include "ball.h"

#include <QDebug>

PhysEngine::PhysEngine(Ball& ball, QObject* parent) : QObject(parent), m_ball(ball), m_worker(*this, ball.physData())
{
    m_timeScale = 1.0f;
    m_vectorG = QVector2D(0, -2800.0f);

    m_topWall = 0.0f;
    m_bottomWall = 0.0f;
    m_leftWall = 0.0f;
    m_rightWall = 0.0f;

    connect(&m_thread, &QThread::started, &m_worker, &PhysWorker::doWork);
    connect(&m_worker, &PhysWorker::started, this, &PhysEngine::started);
    connect(&m_worker, &PhysWorker::resultReady, this, &PhysEngine::resultReady, Qt::DirectConnection);
    connect(&m_worker, &PhysWorker::finished, &m_thread, &QThread::quit, Qt::DirectConnection);
    connect(&m_worker, &PhysWorker::finished, this, &PhysEngine::finished);

    // Log connect
    connect(&m_worker, &PhysWorker::started, []() { qDebug() << "PhysEngine: started"; });
    connect(&m_worker, &PhysWorker::finished, []() { qDebug() << "PhysEngine: finished"; });

    m_worker.moveToThread(&m_thread);
}

//---------------------------------------------------------

void PhysEngine::start()
{
    m_thread.start();
}

void PhysEngine::stop()
{
    m_worker.stop();
    m_thread.wait();
}

//---------------------------------------------------------

void PhysEngine::resultReady(PhysData const& physData)
{
    emit updatePhysData(physData);
    m_ball.setPhysData(physData);
    emit updateLocation(physData.location());
}

//---------------------------------------------------------

bool PhysEngine::isWork() const
{
    return m_worker.isWork();
}

float PhysEngine::timeScale() const
{
    return m_timeScale;
}

const QVector2D& PhysEngine::vectorG() const
{
    return m_vectorG;
}

//---------------------------------------------------------

float PhysEngine::topWall() const
{
    return m_topWall;
}

float PhysEngine::leftWall() const
{
    return m_leftWall;
}

float PhysEngine::bottomWall() const
{
    return m_bottomWall;
}

float PhysEngine::rightWall() const
{
    return m_rightWall;
}

//---------------------------------------------------------

void PhysEngine::setTimeScale(float scale)
{
    m_timeScale = scale;
}

void PhysEngine::setVectorG(QVector2D const& vectorG)
{
    this->m_vectorG = vectorG;
}

//---------------------------------------------------------

void PhysEngine::setTopWall(float yLine)
{
    m_topWall = yLine;
}

void PhysEngine::setLeftWall(float xLine)
{
    m_leftWall = xLine;
}

void PhysEngine::setBottomWall(float yLine)
{
    m_bottomWall = yLine;
}

void PhysEngine::setRightWall(float xLine)
{
    m_rightWall = xLine;
}
