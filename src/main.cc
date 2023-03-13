#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Facade facade;
  s21::Controller controller(&facade);
  MainWindow w(&controller);
  w.show();
  return a.exec();
}
