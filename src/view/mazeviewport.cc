#include "mazeviewport.h"

#include "maze.h"

MazeViewport::MazeViewport(QWidget* parent)
    : QGraphicsView{parent},
      cell_width_(),
      cell_height_(),
      scene_(new Scene),
      solution_(nullptr) {
  scene_->setSceneRect(QRectF(0, 0, kViewportSize, kViewportSize));
  scene_->setBackgroundBrush(QBrush(QColor(25, 50, 60)));
  setRenderHints(QPainter::Antialiasing);
  setScene(scene_);
}

MazeViewport::~MazeViewport() { delete scene_; }

void MazeViewport::drawBackground(QPainter* painter, const QRectF& rect) {
  painter->save();
  painter->setPen(Qt::NoPen);
  painter->setBrush(QBrush(QColor(25, 50, 60)));
  painter->drawRoundedRect(rect, 5, 5);
  painter->restore();
}

auto MazeViewport::Render(const s21::Maze* maze) -> void {
  if (solution_) {
    scene_->removeItem(solution_);
  }
  scene_->clear();
  s21::Field::Size size = maze->get_size();
  cell_width_ = kViewportSize / size.width;
  cell_height_ = kViewportSize / size.height;
  for (int i = 0; i < size.height; i++) {
    for (int j = 0; j < size.width; j++) {
      if (maze->get_right_walls()[i][j] && j < size.width - 1) {
        QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect;
        shadow->setBlurRadius(20);
        shadow->setOffset(2, 2);
        const float xFrom = cell_width_ * j + cell_width_;
        const float xTo = xFrom;
        const float yFrom = cell_height_ * i;
        const float yTo = yFrom + cell_height_;
        QGraphicsLineItem* item = new QGraphicsLineItem(xFrom, yFrom, xTo, yTo);
        item->setGraphicsEffect(shadow);
        item->setPen(QPen(QColor(169, 63, 85), 2));
        scene_->addItem(item);
      }
      if (maze->get_bottom_walls()[i][j] && i < size.height - 1) {
        QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect;
        shadow->setBlurRadius(20);
        shadow->setOffset(2, 2);
        const float xFrom = cell_width_ * j;
        const float xTo = xFrom + cell_width_;
        const float yFrom = cell_height_ * i + cell_height_;
        const float yTo = yFrom;
        QGraphicsLineItem* item = new QGraphicsLineItem(xFrom, yFrom, xTo, yTo);
        item->setGraphicsEffect(shadow);
        item->setPen(QPen(QColor(169, 63, 85), 2));
        scene_->addItem(item);
      }
    }
  }
  show();

  connect(scene_, &Scene::mousePressed, this, &MazeViewport::OnMousePressed);
  connect(scene_, &Scene::mouseReleased, this, &MazeViewport::OnMouseReleased);
}

auto MazeViewport::dragEnterEvent(QDragEnterEvent* event) -> void {
  event->acceptProposedAction();
}

auto MazeViewport::dragMoveEvent(QDragMoveEvent* event) -> void {
  event->acceptProposedAction();
}

auto MazeViewport::dragLeaveEvent(QDragLeaveEvent* event) -> void {
  event->accept();
}

auto MazeViewport::dropEvent(QDropEvent* event) -> void {
  const QMimeData* mimeData = event->mimeData();

  if (mimeData->hasUrls()) {
    emit FileDroped(mimeData->urls().at(0).toLocalFile());
  }
}

void MazeViewport::OnMousePressed(QPointF point) {
  solve_from_ = s21::Coordinate{static_cast<size_t>(point.x() / cell_width_),
                                static_cast<size_t>(point.y() / cell_height_)};
}

void MazeViewport::OnMouseReleased(QPointF point) {
  double x = point.x();
  double y = point.y();
  if (x > 500) x = 499;
  if (y > 500) y = 499;
  if (x < 0) x = 0;
  if (y < 0) y = 0;

  solve_to_ = s21::Coordinate{static_cast<size_t>(x / cell_width_),
                              static_cast<size_t>(y / cell_height_)};
  emit PathCreated(solve_from_, solve_to_);
}

void MazeViewport::OnMazeSolved(s21::Maze::Coordinates* solution) {
  if (solution_) {
    scene_->removeItem(solution_);
  }
  float x = solution->top().x * cell_width_ + cell_width_ / 2;
  float y = solution->top().y * cell_height_ + cell_height_ / 2;
  solution->pop();

  QPainterPath solution_path(QPointF(x, y));
  while (!solution->empty()) {
    x = solution->top().x * cell_width_ + cell_width_ / 2;
    y = solution->top().y * cell_height_ + cell_height_ / 2;
    solution_path.lineTo(x, y);
    solution->pop();
  }
  solution_ = scene_->addPath(solution_path, QPen(QColor(210, 210, 220)));

  clearFocus();
}
