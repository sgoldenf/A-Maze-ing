#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(s21::Controller* controller)
    : ui(new Ui::MainWindow),
      cave_tab_(CaveTab(this, controller)),
      maze_tab_(MazeTab(this, controller)),
      controller_(controller),
      warning_widget_(new QMessageBox) {
  ui->setupUi(this);
  ui->stackedWidget->addWidget(&cave_tab_);
  ui->stackedWidget->addWidget(&maze_tab_);
  ui->stackedWidget->setCurrentWidget(&maze_tab_);
  connect(ui->actionMaze, &QAction::triggered, this,
          &MainWindow::OnMazeMenuTriggered);
  connect(ui->actionCave, &QAction::triggered, this,
          &MainWindow::OnCaveMenuTriggered);
  connect(ui->actionOpen, &QAction::triggered, this,
          &MainWindow::OnOpenMenuTriggered);
  connect(ui->actionSave, &QAction::triggered, this,
          &MainWindow::OnSaveMenuTriggered);
  connect(&maze_tab_, &MazeTab::ErrorOccured, this,
          &MainWindow::OnErrorOccured);
}

MainWindow::~MainWindow() {
  delete warning_widget_;
  delete ui;
}

void MainWindow::OnMazeMenuTriggered() {
  if (ui->stackedWidget->currentWidget() != &maze_tab_) {
    ui->stackedWidget->setCurrentWidget(&maze_tab_);
  }
}

void MainWindow::OnCaveMenuTriggered() {
  if (ui->stackedWidget->currentWidget() != &cave_tab_) {
    ui->stackedWidget->setCurrentWidget(&cave_tab_);
  }
}

void MainWindow::OnOpenMenuTriggered() {
  QString filepath = QFileDialog::getOpenFileName(
      this, nullptr, QDir::homePath(), "TXT (*.txt)", 0,
      QFileDialog::DontUseNativeDialog);
  if (!filepath.isEmpty()) {
    if (!filepath.endsWith(".txt")) {
      filepath += ".txt";
    }
    if (ui->stackedWidget->currentWidget() == &cave_tab_) {
      cave_tab_.OpenFile(filepath);
    } else {
      maze_tab_.OpenFile(filepath);
    }
  }
}

void MainWindow::OnSaveMenuTriggered() {
  QString filepath = QFileDialog::getSaveFileName(
      this, nullptr, QDir::homePath(), "TXT (*.txt", 0,
      QFileDialog::DontUseNativeDialog);
  if (!filepath.isEmpty()) {
    if (!filepath.endsWith(".txt")) {
      filepath += ".txt";
    }
    if (ui->stackedWidget->currentWidget() == &cave_tab_) {
      controller_->SaveCave(filepath.toStdString());
    } else {
      controller_->SaveMaze(filepath.toStdString());
    }
  }
}

void MainWindow::OnErrorOccured(std::string error) {
  warning_widget_->setText("Error: " + QString::fromStdString(error));
  warning_widget_->show();
}
