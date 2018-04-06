#include "mediator.h"

#include "phys_engine.h"
#include "renderer.h"

Mediator::Mediator(Renderer& renderer, PhysEngine& physEngine, QObject* parent) : QObject(parent)
{
    connect(&physEngine, &PhysEngine::newLocation, &renderer, &Renderer::newLocation, Qt::DirectConnection);
}
