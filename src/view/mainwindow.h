#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>

#include "cavetab.h"
#include "controller.h"
#include "mazetab.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(s21::Controller* controller);
  ~MainWindow();

 public slots:
  auto OnMazeMenuTriggered() -> void;
  auto OnCaveMenuTriggered() -> void;
  auto OnOpenMenuTriggered() -> void;
  auto OnSaveMenuTriggered() -> void;
  auto OnErrorOccured(std::string error) -> void;

 private:
  Ui::MainWindow* ui;
  CaveTab cave_tab_;
  MazeTab maze_tab_;
  s21::Controller* controller_;
  QMessageBox* warning_widget_;
};
#endif  // MAINWINDOW_H
