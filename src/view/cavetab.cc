#include "cavetab.h"

#include "ui_cavetab.h"

CaveTab::CaveTab(QWidget* parent, s21::Controller* controller)
    : QWidget(parent),
      ui(new Ui::CaveTab),
      controller_(controller),
      timer_(new QTimer) {
  ui->setupUi(this);
  connect(ui->generateButton, &QPushButton::clicked, this,
          &CaveTab::OnGenerateButtonClicked);
  connect(ui->nextStepButton, &QPushButton::clicked, this,
          &CaveTab::OnNextStepButtonClicked);
  connect(ui->runButton, &QPushButton::clicked, this,
          &CaveTab::OnRunButtonClicked);
  connect(ui->resetButton, &QPushButton::clicked, this,
          &CaveTab::OnResetButtonClicked);
  connect(timer_, &QTimer::timeout, this, &CaveTab::OnTimeout);
  connect(ui->viewport, &CaveViewport::fileDroped, this,
          &CaveTab::OnFileDroped);
}

CaveTab::~CaveTab() {
  delete timer_;
  delete ui;
}

void CaveTab::OpenFile(QString filepath) {
  try {
    controller_->LoadCave(filepath.toStdString());
    ui->viewport->Render(controller_->get_cave());
    ui->iterations->setText(QString::number(0));
    ui->nextStepButton->setDisabled(false);
    ui->runButton->setDisabled(false);
    setFocus();
  } catch (std::exception& e) {
    emit ErrorOccured(e.what());
  }
}

void CaveTab::OnGenerateButtonClicked() {
  if (timer_->isActive()) {
    ui->runButton->setText("Run");
    timer_->stop();
  }
  int height = ui->heightEdit->value();
  int width = ui->widthEdit->value();
  double chance = ui->chanceEdit->value();
  controller_->GenerateCave(s21::Field::Size{width, height}, chance);
  ui->viewport->Render(controller_->get_cave());
  ui->iterations->setText(QString::number(0));
  ui->nextStepButton->setDisabled(false);
  ui->runButton->setDisabled(false);
}

void CaveTab::OnNextStepButtonClicked() {
  int birth = ui->birthLimitEdit->value();
  int death = ui->deathLimitEdit->value();
  if (controller_->CaveIteration(birth, death)) {
    ui->viewport->Render(controller_->get_cave());
    ui->iterations->setText(
        QString::number(ui->iterations->text().toInt() + 1));
  } else {
    timer_->stop();
    ui->runButton->setText("Run");
    ui->nextStepButton->setDisabled(true);
    ui->runButton->setDisabled(true);
  }
}

void CaveTab::OnRunButtonClicked() {
  if (timer_->isActive()) {
    ui->runButton->setText("Run");
    timer_->stop();
    ui->nextStepButton->setDisabled(false);
  } else {
    ui->nextStepButton->setDisabled(true);
    ui->runButton->setText("Stop");
    timer_->start(ui->stepEdit->value());
  }
}

void CaveTab::OnResetButtonClicked() {
  if (timer_->isActive()) {
    ui->runButton->setText("Run");
    timer_->stop();
  }
  controller_->ResetCave();
  ui->viewport->Render(controller_->get_cave());
  ui->iterations->setText(QString::number(0));
  ui->nextStepButton->setDisabled(false);
  ui->runButton->setDisabled(false);
}

void CaveTab::OnFileDroped(QString filepath) { OpenFile(filepath); }

void CaveTab::OnTimeout() { OnNextStepButtonClicked(); }
