#ifndef CAVEVIEWPORT_H
#define CAVEVIEWPORT_H

#include <QDragEnterEvent>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QPainter>

#include "cave.h"
#include "scene.h"

class CaveViewport : public QGraphicsView {
  Q_OBJECT
 signals:
  auto fileDroped(QString) -> void;

 public:
  explicit CaveViewport(QWidget* parent = nullptr);
  ~CaveViewport();
  auto drawBackground(QPainter* painter, const QRectF& rect) -> void;
  auto Render(const s21::Cave* cave) -> void;

 protected:
  auto dragEnterEvent(QDragEnterEvent* event) -> void;
  auto dragMoveEvent(QDragMoveEvent* event) -> void;
  auto dragLeaveEvent(QDragLeaveEvent* event) -> void;
  auto dropEvent(QDropEvent* event) -> void;

 private:
  Scene* scene_;

  const int kViewportSize = 500;
};

#endif  // CAVEVIEWPORT_H
