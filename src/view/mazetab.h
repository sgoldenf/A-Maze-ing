#ifndef MAZE_TAB_H
#define MAZE_TAB_H

#include <QWidget>

#include "controller.h"

namespace Ui {
class MazeTab;
}

class MazeTab : public QWidget {
  Q_OBJECT
 signals:
  auto MazeSolved(s21::Maze::Coordinates*) -> void;
  auto ErrorOccured(std::string error_message) -> void;

 public:
  explicit MazeTab(QWidget* parent = nullptr,
                   s21::Controller* controller = nullptr);
  ~MazeTab();

  auto OpenFile(QString filepath) -> void;

 private slots:
  auto OnGenerateButtonClicked() -> void;
  auto OnPathCreated(s21::Coordinate from, s21::Coordinate to) -> void;
  auto OnFileDroped(QString filepath) -> void;

 private:
  Ui::MazeTab* ui;
  s21::Controller* controller_;
};

#endif  // MAZE_TAB_H
