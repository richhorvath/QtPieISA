#include "isa/mainwindow.hpp"

#include <QDebug>

#include "ui_mainwindow.h"

/**********************************************************************/

MainWindow::MainWindow(const InstVec &inst_vec, QWidget *parent)
    : QMainWindow(parent),
      m_ui_(new Ui::MainWindow),
      m_decoder_(new InstructionDecoder(inst_vec)) {
  m_ui_->setupUi(this);
  for (const auto &inst : inst_vec) {
    qDebug() << inst.opCode() << ": " << static_cast<int>(inst.hexCode());
  }

  m_registers_ = new QVector<Register *>();
  for (int i = 0; i < 4; ++i) {
    m_registers_->push_back(new Register());
  }
  m_registers_->value(1)->writeData(0x01);
  m_registers_->value(2)->writeData(0x01);
  m_decoder_->setRegisters(m_registers_);
  connect(m_ui_->executeButton, &QPushButton::clicked, this,
          &MainWindow::slot_onExecute);
}

/**********************************************************************/

MainWindow::~MainWindow() { delete m_ui_; }

/**********************************************************************/

void MainWindow::slot_onExecute() {
  QString program_string = m_ui_->mainEditor->toPlainText();

  isa::DecodedInstructions instructions = m_decoder_->decode(program_string);

  using namespace isa;
  for (const auto &instruction : instructions) {
    if (instruction.optype() == OpTypes::R) {
      OpCodesHex op_hex = static_cast<OpCodesHex>(instruction.opcode());
      switch (op_hex) {
        case OpCodesHex::SUBTRACT: {
          subtract<uint8_t> sub;
          rTypeInstruction(instruction.source1(), sub, instruction.source2(),
                           instruction.destination());
          break;
        }
        case OpCodesHex::MODULUS: {
          modulus<uint8_t> mod;
          rTypeInstruction(instruction.source1(), mod, instruction.source2(),
                           instruction.destination());
          break;
        }
        case OpCodesHex::BITEWISE_AND: {
          bitwiseAnd<uint8_t> bitwise;
          rTypeInstruction(instruction.source1(), bitwise,
                           instruction.source2(), instruction.destination());
          break;
        }
        case OpCodesHex::ADD: {
          add<uint8_t> add_;
          rTypeInstruction(instruction.source1(), add_, instruction.source2(),
                           instruction.destination());
          break;
        }
      }
    }

    for (int i = 0; i < m_registers_->size(); ++i) {
      qDebug() << m_registers_->value(i)->readData();
    }
  }

  //  isa::multiply<int> mult;
  //  isa::rTypeInstruction(m_registers_->value(0), mult,
  //  m_registers_->value(1),
  //                        m_registers_->value(2));
  //  qDebug() << reg3.readData();
}

/**********************************************************************/
