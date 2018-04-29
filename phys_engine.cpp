#include "phys_engine.h"
#include "ball.h"

#include <QDebug>

PhysEngine::PhysEngine(Ball& ball, QObject* parent) : QObject(parent), ball_(ball), worker_(*this, ball.physData())
{
    timeScale_ = 1.0f;
    vectorG_ = QVector2D(0, -2800.0f);

    topWall_ = 0.0f;
    bottomWall_ = 0.0f;
    leftWall_ = 0.0f;
    rightWall_ = 0.0f;

    connect(&thread_, &QThread::started, &worker_, &PhysWorker::doWork);
    connect(&worker_, &PhysWorker::started, this, &PhysEngine::started);
    connect(&worker_, &PhysWorker::resultReady, this, &PhysEngine::resultReady, Qt::DirectConnection);
    connect(&worker_, &PhysWorker::finished, &thread_, &QThread::quit, Qt::DirectConnection);
    connect(&worker_, &PhysWorker::finished, this, &PhysEngine::finished);

    // Log connect
    connect(&worker_, &PhysWorker::started, []() { qDebug() << "PhysEngine: started"; });
    connect(&worker_, &PhysWorker::finished, []() { qDebug() << "PhysEngine: finished"; });

    worker_.moveToThread(&thread_);
}

//---------------------------------------------------------

void PhysEngine::start()
{
    thread_.start();
}

void PhysEngine::stop()
{
    worker_.stop();
    thread_.wait();
}

//---------------------------------------------------------

void PhysEngine::resultReady(PhysData physData)
{
    ball_.setPhysData(physData);
    emit updateLocation(physData.location());
}

//---------------------------------------------------------

bool PhysEngine::isWork() const
{
    return worker_.isWork();
}

float PhysEngine::timeScale() const
{
    return timeScale_;
}

const QVector2D& PhysEngine::vectorG() const
{
    return vectorG_;
}

//---------------------------------------------------------

float PhysEngine::topWall() const
{
    return topWall_;
}

float PhysEngine::leftWall() const
{
    return leftWall_;
}

float PhysEngine::bottomWall() const
{
    return bottomWall_;
}

float PhysEngine::rightWall() const
{
    return rightWall_;
}

//---------------------------------------------------------

void PhysEngine::setTimeScale(float scale)
{
    timeScale_ = scale;
}

void PhysEngine::setVectorG(const QVector2D& vectorG)
{
    this->vectorG_ = vectorG;
}

//---------------------------------------------------------

void PhysEngine::setTopWall(float yLine)
{
    topWall_ = yLine;
}

void PhysEngine::setLeftWall(float xLine)
{
    leftWall_ = xLine;
}

void PhysEngine::setBottomWall(float yLine)
{
    bottomWall_ = yLine;
}

void PhysEngine::setRightWall(float xLine)
{
    rightWall_ = xLine;
}
