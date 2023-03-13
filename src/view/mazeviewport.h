#ifndef MAZEVIEWPORT_H
#define MAZEVIEWPORT_H

#include <QDragEnterEvent>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QPainter>

#include "maze.h"
#include "scene.h"

class MazeViewport : public QGraphicsView {
  Q_OBJECT
 signals:
  auto PathCreated(s21::Coordinate, s21::Coordinate) -> void;
  auto FileDroped(QString) -> void;

 public:
  explicit MazeViewport(QWidget* parent = nullptr);
  ~MazeViewport();
  auto drawBackground(QPainter* painter, const QRectF& rect) -> void;
  auto Render(const s21::Maze* maze) -> void;

 protected:
  auto dragEnterEvent(QDragEnterEvent* event) -> void;
  auto dragMoveEvent(QDragMoveEvent* event) -> void;
  auto dragLeaveEvent(QDragLeaveEvent* event) -> void;
  auto dropEvent(QDropEvent* event) -> void;

 public slots:
  auto OnMousePressed(QPointF point) -> void;
  auto OnMouseReleased(QPointF point) -> void;
  auto OnMazeSolved(s21::Maze::Coordinates* solution) -> void;

 private:
  float cell_width_;
  float cell_height_;
  Scene* scene_;
  s21::Coordinate solve_from_;
  s21::Coordinate solve_to_;
  QGraphicsPathItem* solution_;

  const float kViewportSize = 500;
};

#endif  // MAZEVIEWPORT_H
