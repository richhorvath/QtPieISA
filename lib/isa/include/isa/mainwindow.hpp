#ifndef LIB_ISA_MAINWINDOW_HPP_
#define LIB_ISA_MAINWINDOW_HPP_

#include <QMainWindow>

#include "isa/config_parser.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(const InstVec &inst_vec, QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
};

#endif  // LIB_ISA_MAINWINDOW_HPP_
