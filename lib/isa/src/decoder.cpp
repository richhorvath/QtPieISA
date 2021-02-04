#include "isa/decoder.hpp"

#include <QObject>
#include <QRegExp>

static const QString register0 = "R0";
static const QString register1 = "R1";
static const QString register2 = "R2";
static const QString register3 = "R3";

/**********************************************************************/

InstructionDecoder::InstructionDecoder(const InstVec &inst_vec) {
  for (const auto &inst : inst_vec) {
    m_opStrToHex_.insert(inst.opCode(), inst.hexCode());
    m_opHextoStr_.insert(inst.hexCode(), inst.opCode());
    m_registerTokens_ = {{register0, true},
                         {register1, true},
                         {register2, true},
                         {register3, true}};
  }
}

/**********************************************************************/

isa::DecodedInstructions InstructionDecoder::decode(
    const QString &program_string) {
  QStringList instructions = program_string.split("\n");
  QVector<isa::Instruction> decoded_instructions;
  for (const auto &str_inst : instructions) {
    qDebug() << str_inst;
    QStringList instruction = str_inst.split(" ");
    QRegExp re("\\d*");
    if (instruction.size() > 2) {
      if (m_registerTokens_.contains(instruction[0])) {
        if (m_registerTokens_.contains(instruction[2])) {
          qDebug() << "r-instruction";
          // build R instruction
          if (m_opStrToHex_.contains(instruction[1])) {
            decoded_instructions.push_back(buildRInstruction(instruction));
          } else {
            qDebug() << "syntax error";
          }
        } else if (instruction.size() > 3 &&
                   m_opStrToHex_.contains(instruction[3])) {
          decoded_instructions.push_back(buildIInstruction(instruction));
        } else if (re.exactMatch(instruction[2])) {
          decoded_instructions.push_back(
              buildIInstructionImmediate(instruction));
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
  return decoded_instructions;
}

/**********************************************************************/

const isa::Instruction InstructionDecoder::buildRInstruction(
    const QStringList &r_inst) {
  isa::Instruction inst;
  inst.setSource1(getInstrRegister(r_inst[0]));
  inst.setSource2(getInstrRegister(r_inst[2]));
  inst.setDestination(getInstrRegister(r_inst[3]));
  inst.setOpCode(m_opStrToHex_.value(r_inst[1]));
  inst.setOpType(isa::OpTypes::R);

  return inst;
}

/**********************************************************************/

const isa::Instruction InstructionDecoder::buildIInstruction(
    const QStringList &r_inst) {
  isa::Instruction inst;
  inst.setSource1(getInstrRegister(r_inst[0]));
  bool ok = true;
  inst.setData(r_inst[2].toUInt(&ok, 16));
  inst.setDestination(getInstrRegister(r_inst[3]));
  inst.setOpCode(m_opStrToHex_.value(r_inst[1]));
  inst.setOpType(isa::OpTypes::I);

  return inst;
}

/**********************************************************************/

const isa::Instruction InstructionDecoder::buildIInstructionImmediate(
    const QStringList &r_inst) {
  isa::Instruction inst;
  bool ok = true;
  inst.setData(r_inst[2].toUInt(&ok, 16));
  inst.setDestination(getInstrRegister(r_inst[0]));
  inst.setOpCode(m_opStrToHex_.value(r_inst[1]));
  inst.setOpType(isa::OpTypes::II);

  return inst;
}
/**********************************************************************/

Register *InstructionDecoder::getInstrRegister(const QString &reg_str) {
  Register *reg = nullptr;
  qDebug() << "Getting register " << reg_str;
  if (register0 == reg_str) {
    reg = m_registers_->value(0);
  } else if (register1 == reg_str) {
    reg = m_registers_->value(1);
  } else if (register2 == reg_str) {
    reg = m_registers_->value(2);
  } else if (register3 == reg_str) {
    reg = m_registers_->value(3);
  }

  qDebug() << "register data " << reg->readData();
  if (reg == nullptr) {
    qDebug() << "YAH FUCKED UP ROCKY";
  }
  return reg;
}
