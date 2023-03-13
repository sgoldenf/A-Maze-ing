#ifndef CAVETAB_H
#define CAVETAB_H

#include <QTimer>
#include <QWidget>

#include "controller.h"

namespace Ui {
class CaveTab;
}

class CaveTab : public QWidget {
  Q_OBJECT
 signals:
  auto ErrorOccured(std::string error_message) -> void;

 public:
  explicit CaveTab(QWidget* parent = nullptr,
                   s21::Controller* controller = nullptr);
  ~CaveTab();

  auto OpenFile(QString filepath) -> void;

 private slots:
  auto OnGenerateButtonClicked() -> void;
  auto OnNextStepButtonClicked() -> void;
  auto OnRunButtonClicked() -> void;
  auto OnResetButtonClicked() -> void;
  auto OnTimeout() -> void;
  auto OnFileDroped(QString filepath) -> void;

 private:
  Ui::CaveTab* ui;
  s21::Controller* controller_;
  QTimer* timer_;
};

#endif  // CAVETAB_H
