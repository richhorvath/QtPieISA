#include "isa/decoder.hpp"

#include <QObject>
#include <QRegExp>

static const QString register0 = "R0";
static const QString register1 = "R1";
static const QString register2 = "R2";
static const QString register3 = "R3";

InstructionDecoder::InstructionDecoder(const InstVec &inst_vec) {
  for (const auto &inst : inst_vec) {
    m_opStrToHex_.insert(inst.opCode(), inst.hexCode());
    m_opHextoStr_.insert(inst.hexCode(), inst.opCode());
  }
}

void InstructionDecoder::decode(const QString &program_string) {
  QStringList instructions = program_string.split("\n");
  for (const auto &str_inst : instructions) {
    qDebug() << str_inst;
    QStringList instruction = str_inst.split(" ");
    QRegExp re("\\d*");
    if (instruction.size() > 2) {
      if (instruction[0] == "R1") {
        if (instruction[2] == "R2") {
          qDebug() << "r-instruction";
          // build R instruction
          if (m_opStrToHex_.contains(instruction[1])) {
            buildRInstruction(instruction);
          } else {
            qDebug() << 'idk wtf opcode that was, try again.';
          }
        } else if (instruction.size() > 3 && instruction[3] == "R2") {
          qDebug() << "Second i-instruction";
          // build second i instruction
        } else if (re.exactMatch(instruction[2])) {
          qDebug() << "i-instruction";
          // build i instruction
        } else {
          qDebug() << "inner syntax error";
        }
      } else if (instruction[0] == "opcode") {
        qDebug() << "j-instruction";
        // build j instruction
      } else {
        qDebug() << "syntax error";
      }
    }
  }
}

/**********************************************************************/

const isa::Instruction &InstructionDecoder::buildRInstruction(
    const QStringList &r_inst) {
  Register *source1 = getInstrRegister(r_inst[0]);
  Register *source2 = getInstrRegister(r_inst[2]);
  Register *destination = getInstrRegister(r_inst[3]);
  uint8_t opcode = m_opStrToHex_.value(r_inst[1]);
  qDebug() << static_cast<int>(opcode);

  return {};
}

/**********************************************************************/

Register *InstructionDecoder::getInstrRegister(const QString &reg_str) {
  Register *reg = nullptr;
  if (register0 == reg_str) {
    reg = m_registers_->value(0);
  } else if (register1 == reg_str) {
    reg = m_registers_->value(1);
  } else if (register2 == reg_str) {
    reg = m_registers_->value(2);
  } else if (register1 == reg_str) {
    reg = m_registers_->value(3);
  }
  return reg;
}
