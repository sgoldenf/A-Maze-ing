#include "mazetab.h"

#include "ui_mazetab.h"

MazeTab::MazeTab(QWidget* parent, s21::Controller* controller)
    : QWidget(parent), ui(new Ui::MazeTab), controller_(controller) {
  ui->setupUi(this);
  connect(ui->generateButton, &QPushButton::clicked, this,
          &MazeTab::OnGenerateButtonClicked);
  connect(ui->viewport, &MazeViewport::PathCreated, this,
          &MazeTab::OnPathCreated);
  connect(this, &MazeTab::MazeSolved, ui->viewport,
          &MazeViewport::OnMazeSolved);
  connect(ui->viewport, &MazeViewport::FileDroped, this,
          &MazeTab::OnFileDroped);
}

MazeTab::~MazeTab() { delete ui; }

void MazeTab::OpenFile(QString filepath) {
  try {
    controller_->LoadMaze(filepath.toStdString());
    ui->viewport->Render(controller_->get_maze());
    setFocus();
  } catch (std::exception& e) {
    emit ErrorOccured(e.what());
  }
}

void MazeTab::OnGenerateButtonClicked() {
  int height = ui->heightEdit->text().toInt();
  int width = ui->widthEdit->text().toInt();
  try {
    controller_->GenerateMaze(s21::Field::Size{width, height});
    ui->viewport->Render(controller_->get_maze());
  } catch (std::exception& e) {
    emit ErrorOccured(e.what());
  }
}

void MazeTab::OnPathCreated(s21::Coordinate from, s21::Coordinate to) {
  emit MazeSolved(controller_->SolveMaze(from, to));
}

void MazeTab::OnFileDroped(QString filepath) { OpenFile(filepath); }
