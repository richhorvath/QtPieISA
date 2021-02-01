#include "isa/mainwindow.hpp"

#include <QDebug>

#include "isa/instructions.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(const InstVec &inst_vec, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  for (const auto &inst : inst_vec) {
    qDebug() << inst.opCode() << ": " << static_cast<int>(inst.hexCode());
  }
}

MainWindow::~MainWindow() { delete ui; }
