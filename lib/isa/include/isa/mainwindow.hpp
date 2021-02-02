#ifndef LIB_ISA_MAINWINDOW_HPP_
#define LIB_ISA_MAINWINDOW_HPP_

#include <QMainWindow>

#include "isa/config_parser.hpp"
#include "isa/decoder.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 signals:
  void signal_programExecuted(const QString &program);

 public:
  explicit MainWindow(const InstVec &inst_vec, QWidget *parent = nullptr);
  ~MainWindow();

 private:
  void slot_onExecute();
  Ui::MainWindow *m_ui_;
  InstructionDecoder *m_decoder_;
  QVector<Register *> *m_registers_;
};

#endif  // LIB_ISA_MAINWINDOW_HPP_
