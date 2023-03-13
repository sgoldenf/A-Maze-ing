#include "scene.h"

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit mousePressed(event->scenePos());
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit mouseReleased(event->scenePos());
}
