#include "caveviewport.h"

CaveViewport::CaveViewport(QWidget* parent)
    : QGraphicsView{parent}, scene_(new Scene) {
  scene_->setSceneRect(QRectF(0, 0, kViewportSize, kViewportSize));
  setRenderHints(QPainter::Antialiasing);
  setScene(scene_);
}

CaveViewport::~CaveViewport() { delete scene_; }

void CaveViewport::drawBackground(QPainter* painter, const QRectF& rect) {
  painter->save();
  painter->setPen(Qt::NoPen);
  painter->setBrush(QBrush(QColor(25, 50, 60)));
  painter->drawRect(rect);
  painter->restore();
}

void CaveViewport::Render(const s21::Cave* cave) {
  scene_->clear();
  s21::Field::Size size = cave->get_size();
  float cell_width = kViewportSize / float(size.width);
  float cell_height = kViewportSize / float(size.height);
  for (int i = 0; i < size.height; i++) {
    for (int j = 0; j < size.width; j++) {
      QBrush brush(QColor(25, 50, 60));
      if (cave->get_cells()[i][j]) {
        brush.setColor(QColor(169, 63, 85));
      }
      QRectF rect(cell_width * j, cell_height * i, cell_width + 0.5f,
                  cell_height);
      scene_->addRect(rect, QPen(QColor(25, 50, 60)), brush);
    }
  }
  show();
}

auto CaveViewport::dragEnterEvent(QDragEnterEvent* event) -> void {
  event->acceptProposedAction();
}

auto CaveViewport::dragMoveEvent(QDragMoveEvent* event) -> void {
  event->acceptProposedAction();
}

auto CaveViewport::dragLeaveEvent(QDragLeaveEvent* event) -> void {
  event->accept();
}

auto CaveViewport::dropEvent(QDropEvent* event) -> void {
  const QMimeData* mimeData = event->mimeData();

  if (mimeData->hasUrls()) {
    emit fileDroped(mimeData->urls().at(0).toLocalFile());
  }
}
