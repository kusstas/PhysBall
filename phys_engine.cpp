#include "phys_engine.h"
#include "phys_worker.h"
#include "ball.h"

#include <QThread>

PhysEngine::PhysEngine(Ball& ball, QObject* parent) : QObject(parent), worker(*this, ball)
{
    this->ball = &ball;

    timeScale = 1.0f;
    vectorG = Vector2(0, -9.8f);

    topWall = 0.0f;
    bottomWall = 0.0f;
    leftWall = 0.0f;
    rightWall = 0.0f;


    thread = new QThread();
    qRegisterMetaType<PhysData>("PhysData");
    connect(&worker, &PhysWorker::resultReady, this, &PhysEngine::resultReady, Qt::DirectConnection);
    connect(&worker, &PhysWorker::finished, thread, &QThread::quit);
    connect(thread, &QThread::started, &worker, &PhysWorker::work);

    worker.moveToThread(thread);
}

PhysEngine::~PhysEngine()
{
    thread->quit();
    thread->deleteLater();
}

//---------------------------------------------------------

void PhysEngine::start()
{
    thread->start();
    emit started();
}

float PhysEngine::getTimeScale() const
{
    return timeScale;
}

const Vector2& PhysEngine::getVectorG() const
{
    return vectorG;
}

//---------------------------------------------------------

float PhysEngine::getTopWall() const
{
    return topWall;
}

float PhysEngine::getLeftWall() const
{
    return leftWall;
}

float PhysEngine::getBottomWall() const
{
    return bottomWall;
}

float PhysEngine::getRightWall() const
{
    return rightWall;
}

//---------------------------------------------------------

void PhysEngine::setTimeScale(float scale)
{
    timeScale = scale;
}

void PhysEngine::setVectorG(const Vector2& vectorG)
{
    this->vectorG = vectorG;
}

//---------------------------------------------------------

void PhysEngine::setTopWall(float yLine)
{
    topWall = yLine;
}

void PhysEngine::setLeftWall(float xLine)
{
    leftWall = xLine;
}

void PhysEngine::setBottomWall(float yLine)
{
    bottomWall = yLine;
}

void PhysEngine::setRightWall(float xLine)
{
    rightWall = xLine;
}

//---------------------------------------------------------

void PhysEngine::resultReady(PhysData physData)
{
    ball->setPhysData(physData);
    emit newLocation(physData.getLocation());
}
