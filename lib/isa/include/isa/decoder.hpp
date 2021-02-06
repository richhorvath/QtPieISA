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
  isa::DecodedInstructions decode(const QString &program_string);

 private:
  /**
   * @brief buildRInstruction
   * @param r_inst
   */
  const isa::Instruction buildRInstruction(const QStringList &r_inst);

  /**
   * @brief buildIInstruction
   * @param i_inst
   * @return
   */
  const isa::Instruction buildIInstruction(const QStringList &i_inst);
  /**
   * @brief buildIInstruction
   * @param i_inst
   * @return
   */
  const isa::Instruction buildIInstructionImmediate(const QStringList &i_inst);

  /**
   * @brief buildJInstruction
   * @param j_inst
   * @return
   */
  const isa::Instruction buildJInstruction(const QStringList &j_inst);
  /**
   * @brief getInstrRegister
   * @param reg_str
   * @return
   */
  uint8_t getInstrRegister(const QString &reg_str);

  QMap<QString, uint8_t> m_opStrToHex_;
  QMap<uint8_t, QString> m_opHextoStr_;
  QMap<QString, bool> m_registerTokens_;
};
#endif  // LIB_ISA_COMMAND_PARSER_HPP_
