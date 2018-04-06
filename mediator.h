#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <QObject>

class Renderer;
class PhysEngine;

class Mediator : public QObject
{

public:

    explicit Mediator(Renderer& renderer, PhysEngine& physEngine, QObject* parent = nullptr);
};

#endif // MEDIATOR_H
