#ifndef RENDER_WORKER_H
#define RENDER_WORKER_H

#include <QObject>

#include "vector2.h"

class Renderer;

class RenderWorker : public QObject
{
    Q_OBJECT

public:

    explicit RenderWorker(Renderer& owner, QObject* parent = nullptr);

signals:

    void started();
    void finished();

    void drawBall(Vector2 location);

public slots:

    void work();
    void stop();

    void update(Vector2 location);

private:

    Renderer* owner;
    bool isWork;

    Vector2 locationBall;

};

#endif // RENDER_WORKER_H
