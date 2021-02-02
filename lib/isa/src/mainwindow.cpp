#include "isa/mainwindow.hpp"

#include <QDebug>

#include "ui_mainwindow.h"

MainWindow::MainWindow(const InstVec &inst_vec, QWidget *parent)
    : QMainWindow(parent),
      m_ui_(new Ui::MainWindow),
      m_decoder_(new InstructionDecoder(inst_vec)) {
  m_ui_->setupUi(this);
  for (const auto &inst : inst_vec) {
    qDebug() << inst.opCode() << ": " << static_cast<int>(inst.hexCode());
  }

  m_registers_ = new QVector<Register *>();
  for (int i = 0; i < 3; ++i) {
    m_registers_->push_back(new Register());
  }
  m_decoder_->setRegisters(m_registers_);
  connect(m_ui_->executeButton, &QPushButton::clicked, this,
          &MainWindow::slot_onExecute);
}

MainWindow::~MainWindow() { delete m_ui_; }

void MainWindow::slot_onExecute() {
  QString program_string = m_ui_->mainEditor->toPlainText();

  m_decoder_->decode(program_string);

  //  isa::multiply<int> mult;
  //  isa::rTypeInstruction(&reg1, mult, &reg2, &reg3);
  //  qDebug() << reg3.readData();
}
