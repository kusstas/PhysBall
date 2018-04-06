#ifndef RENDERER_H
#define RENDERER_H

#include <QObject>
#include <QThread>

#include "vector2.h"
#include "render_worker.h"

class Renderer : public QObject
{
    Q_OBJECT

public:

    explicit Renderer(QObject* parent = nullptr);
    ~Renderer();

    void start();
    void setSize(const Vector2& size);

signals:

    void update(Vector2 location);

public slots:

    void newLocation(Vector2 location);

private:

    RenderWorker worker;
    QThread thread;

    Vector2 size;

};

#endif // RENDERER_H
