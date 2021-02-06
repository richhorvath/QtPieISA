#include "isa/mainwindow.hpp"

#include <QDebug>

#include "isa/alu.hpp"
#include "isa/instructions.hpp"
#include "ui_mainwindow.h"

/**********************************************************************/

MainWindow::MainWindow(const InstVec &inst_vec, QWidget *parent)
    : QMainWindow(parent),
      m_ui_(new Ui::MainWindow),
      m_decoder_(new InstructionDecoder(inst_vec)),
      m_reg_table_(new QStandardItemModel(this)),
      m_mem_table_(new QStandardItemModel(this)) {
  m_ui_->setupUi(this);
  setupRegisters();
  setupMemory();
  connect(m_ui_->executeButton, &QPushButton::clicked, this,
          &MainWindow::slot_onExecute);
}

/**********************************************************************/

MainWindow::~MainWindow() { delete m_ui_; }

/**********************************************************************/

void MainWindow::slot_onExecute() {
  QString program_string = m_ui_->mainEditor->toPlainText();

  if (program_string.size() > 0) {
    isa::DecodedInstructions instructions = m_decoder_->decode(program_string);
    clearData();
    using namespace isa;
    for (const auto &instruction : instructions) {
      OpCodesHex op_hex = static_cast<OpCodesHex>(instruction.opcode());
      switch (op_hex) {
        case OpCodesHex::SUBTRACT: {
          ALU::subtract<uint8_t> sub;
          rTypeInstruction(m_registers_[instruction.source1()], sub,
                           m_registers_[instruction.source2()],
                           m_registers_[instruction.destination()]);
          break;
        }
        case OpCodesHex::MULTIPLY: {
          ALU::multiply<uint8_t> mod;
          rTypeInstruction(m_registers_[instruction.source1()], mod,
                           m_registers_[instruction.source2()],
                           m_registers_[instruction.destination()]);
          break;
        }
        case OpCodesHex::BITEWISE_AND: {
          ALU::bitwiseAnd<uint8_t> bitwise;
          rTypeInstruction(m_registers_[instruction.source1()], bitwise,
                           m_registers_[instruction.source2()],
                           m_registers_[instruction.destination()]);
          break;
        }
        case OpCodesHex::ADD: {
          ALU::add<uint8_t> add_;
          rTypeInstruction(m_registers_[instruction.source1()], add_,
                           m_registers_[instruction.source2()],
                           m_registers_[instruction.destination()]);
          break;
        }

        case OpCodesHex::LOAD_IMMEDIATE: {
          m_registers_[0]->writeData(0x23);
          iTypeInstructionImmediate(m_registers_[instruction.destination()],
                                    instruction.data());

          m_registers_[0]->readData();
          break;
        }
        case OpCodesHex::STORE: {
          m_memory_[instruction.data()] =
              m_registers_[instruction.destination()]->readData();
          break;
        }

        case OpCodesHex::AND:
        case OpCodesHex::MODULUS_IMMEDIATE:
        case OpCodesHex::SUBTRACT_IMMEDIATE:
        case OpCodesHex::SUBTRACT_NEGATIVE:
        case OpCodesHex::MULTIPLY_IMMEDIATE:
        case OpCodesHex::DIVIDE_IMMEDIATE:
        case OpCodesHex::ADD_IMMEDIATE:
        case OpCodesHex::MULTIPLY:
        case OpCodesHex::MULTIPY_NEGATIVE:
        case OpCodesHex::DIVIDE:
        case OpCodesHex::DIVIDE_NEGATIVE:
        case OpCodesHex::BITEWISE_XAND:
        case OpCodesHex::XAND:
        case OpCodesHex::BITEWISE_XOR:
        case OpCodesHex::XOR:
        case OpCodesHex::BITEWISE_OR:
        case OpCodesHex::OR:
        case OpCodesHex::ADD_NEGATIVE:
        case OpCodesHex::LESS_THAN:
        case OpCodesHex::LEFT_SHIFT:
        case OpCodesHex::LESS_THAN_EQUAL:
        case OpCodesHex::EQUAL:
        case OpCodesHex::GREATER_THAN:
        case OpCodesHex::GREATER_THAN_EQUAL:
        case OpCodesHex::RIGHT_SHIFT:
        case OpCodesHex::BREAK:
        case OpCodesHex::CALL:
        case OpCodesHex::CATCH:
        case OpCodesHex::COPY:
        case OpCodesHex::COPY_ARRAY:
        case OpCodesHex::FOR:
        case OpCodesHex::GO_TO_ADDRESS:
        case OpCodesHex::GO_TO_REGISTER:
        case OpCodesHex::LOAD_NULL:
        case OpCodesHex::MOVE:
        case OpCodesHex::NOOP:
        case OpCodesHex::ON_BREAK:
        case OpCodesHex::ON_FALSE:
        case OpCodesHex::ON_NULL:
        case OpCodesHex::ON_TRUE:
        case OpCodesHex::RETHROW:
        case OpCodesHex::STORE_NOW:
        case OpCodesHex::THROW:
        case OpCodesHex::TO_ARRAY:
        case OpCodesHex::TRY:
        case OpCodesHex::TYPEOF:
        case OpCodesHex::WHILE:
        default:
          break;
      }
    }
    updateTables();
  }
}

/**********************************************************************/

QString MainWindow::toHexString(uint8_t hex) {
  QString prefixed = "0x";
  if (hex < 0x10) {
    prefixed += "0";
  }
  QString number = QString::number(hex, 16).toUpper();
  prefixed = prefixed + number;
  return prefixed;
}

/**********************************************************************/

void MainWindow::updateTables() {
  for (int i = 0; i < m_registers_.size(); ++i) {
    auto index = m_reg_table_->index(i, 1);
    QString str = toHexString(m_registers_[i]->readData());
    m_reg_table_->setData(index, str);
  }
  for (int i = 0; i < m_memory_.size(); ++i) {
    auto index = m_mem_table_->index(i, 1);
    m_mem_table_->setData(index, toHexString(m_memory_.value(i)));
  }
}

/**********************************************************************/

void MainWindow::clearData() {
  for (int i = 0; i < m_registers_.size(); ++i) {
    auto index = m_reg_table_->index(i, 1);
    m_registers_[i]->writeData(0x00);
    QString str = toHexString(0x00);
    m_reg_table_->setData(index, str);
  }
  for (int i = 0; i < m_memory_.size(); ++i) {
    auto index = m_mem_table_->index(i, 1);
    m_memory_[i] = 0x00;
    m_mem_table_->setData(index, toHexString(0x00));
  }
}

/**********************************************************************/

void MainWindow::setupRegisters() {
  m_reg_table_->setHorizontalHeaderLabels({{"Register"}, {"Value"}});
  for (int i = 0; i < 4; ++i) {
    m_registers_.push_back(std::make_shared<Register>());
    QList<QStandardItem *> items{new QStandardItem("R" + QString::number(i)),
                                 new QStandardItem("0x00")};
    m_reg_table_->appendRow(items);
  }
  m_ui_->registerTable->setModel(m_reg_table_);
  m_ui_->registerTable->horizontalHeader()->setStretchLastSection(true);
  m_ui_->registerTable->verticalHeader()->setVisible(false);
}

/**********************************************************************/

void MainWindow::setupMemory() {
  m_mem_table_->setHorizontalHeaderLabels({{"Location"}, {"Value"}});
  for (int i = 0; i < 256; ++i) {
    m_memory_.push_back(0x00);
    QList<QStandardItem *> items{new QStandardItem(QString::number(i)),
                                 new QStandardItem("0x00")};
    m_mem_table_->appendRow(items);
  }
  m_ui_->memoryTable->setModel(m_mem_table_);
  m_ui_->memoryTable->horizontalHeader()->setStretchLastSection(true);
  m_ui_->memoryTable->verticalHeader()->setVisible(false);
}

/**********************************************************************/
