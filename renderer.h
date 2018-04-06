#ifndef RENDERER_H
#define RENDERER_H

#include <QObject>

class Renderer : public QObject
{
    Q_OBJECT

public:

    explicit Renderer(QObject *parent = nullptr);

public slots:

    void draw();

};

#endif // RENDERER_H