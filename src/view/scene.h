#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMimeData>

class Scene : public QGraphicsScene {
  Q_OBJECT

 signals:
  auto mousePressed(QPointF) -> void;
  auto mouseReleased(QPointF) -> void;
  auto mouseHold(QPointF) -> void;

 protected:
  auto mousePressEvent(QGraphicsSceneMouseEvent *event) -> void;
  auto mouseReleaseEvent(QGraphicsSceneMouseEvent *event) -> void;
  auto mouseHoldEvent(QGraphicsSceneMouseEvent *event) -> void;
};

#endif  // SCENE_H
