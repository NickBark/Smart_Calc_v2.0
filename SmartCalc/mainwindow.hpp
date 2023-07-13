#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dependencies.hpp"
#include "mainframe.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

  QMenuBar* menuBar;
  QMenu* menu;

  MainFrame* mainFrame;

 private slots:
  void slotMenuBase();
  void slotMenuCredit();
  void slotMenuDeposit();

 private:
  Ui::MainWindow* ui;
};
#endif  // MAINWINDOW_H
