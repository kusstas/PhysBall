#ifndef RENDERER_H
#define RENDERER_H

#include <QObject>
#include <QThread>

#include "render_worker.h"

class Renderer : public QObject
{
    Q_OBJECT

public:

    explicit Renderer(QObject* parent = nullptr);

    bool isWork() const;

signals:

    void started();
    void finished();

    void draw(QVector2D const& location);
    void updateLocation(QVector2D const& location);

public slots:

    void start();
    void stop();

private:

    RenderWorker m_worker;
    QThread m_thread;

};

#endif // RENDERER_H
