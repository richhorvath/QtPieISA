#ifndef LIB_ISA_COMMAND_PARSER_HPP_
#define LIB_ISA_COMMAND_PARSER_HPP_

#include <QDebug>
#include <QMap>
#include <QString>

#include "config_parser.hpp"
#include "isa/instructions.hpp"

/**
 * @brief The CommandParser class
 */
class InstructionDecoder {
 public:
  /**
   * @brief CommandParser
   * @param inst_vec
   */
  InstructionDecoder(const InstVec &inst_vec);

  /**
   * @brief decode
   * @param program_string
   * @return
   */
  void decode(const QString &program_string);

  /**
   * @brief setRegisters
   * @param registers
   */
  void setRegisters(QVector<Register *> *registers) {
    m_registers_ = registers;
  }

 private:
  /**
   * @brief buildRInstruction
   * @param r_inst
   */
  const isa::Instruction &buildRInstruction(const QStringList &r_inst);
  Register *getInstrRegister(const QString &reg_str);

  QMap<QString, uint8_t> m_opStrToHex_;
  QMap<uint8_t, QString> m_opHextoStr_;
  QVector<Register *> *m_registers_;
};
#endif  // LIB_ISA_COMMAND_PARSER_HPP_
