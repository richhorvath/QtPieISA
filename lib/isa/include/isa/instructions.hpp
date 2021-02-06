#ifndef LIB_ISA_INSTRUCTIONS_HPP_
#define LIB_ISA_INSTRUCTIONS_HPP_

#include <QMap>
#include <QString>
#include <QVector>
#include <memory>

#include "isa/register.hpp"

namespace isa {

/**********************************************************************/

/**
 * @brief The OpCodesHex enum
 * OpCode Enumerations
 */
enum class OpCodesHex : uint8_t {
  SUBTRACT = 0x01,
  MODULUS,
  BITEWISE_AND,
  AND,
  MODULUS_IMMEDIATE,
  SUBTRACT_IMMEDIATE,
  SUBTRACT_NEGATIVE,
  MULTIPLY_IMMEDIATE,
  DIVIDE_IMMEDIATE,
  ADD_IMMEDIATE,
  LOAD_IMMEDIATE,
  MULTIPLY,
  MULTIPY_NEGATIVE,
  DIVIDE,
  DIVIDE_NEGATIVE,
  BITEWISE_XAND,
  XAND,
  BITEWISE_XOR,
  XOR,
  BITEWISE_OR,
  OR,
  ADD,
  ADD_NEGATIVE,
  LOAD,
  LESS_THAN,
  LEFT_SHIFT,
  LESS_THAN_EQUAL,
  EQUAL,
  GREATER_THAN,
  GREATER_THAN_EQUAL,
  RIGHT_SHIFT,
  BREAK,
  CALL,
  CATCH,
  COPY,
  COPY_ARRAY,
  FOR,
  GO_TO_ADDRESS,
  GO_TO_REGISTER,
  LOAD_NULL,
  MOVE,
  NOOP,
  ON_BREAK,
  ON_FALSE,
  ON_NULL,
  ON_TRUE,
  RETHROW,
  STORE,
  STORE_NOW,
  THROW,
  TO_ARRAY,
  TRY,
  TYPEOF,
  WHILE
};

/**********************************************************************/

enum class OpTypes : uint8_t { R = 0x00, II, I, J };

/**********************************************************************/

/**
 *@brief
 * Template function to help launch rtype instructions.
 */
template <typename Op>
void rTypeInstruction(std::shared_ptr<Register> source1, Op opFunc,
                      std::shared_ptr<Register> source2,
                      std::shared_ptr<Register> dest) {
  auto result = opFunc(source1->readData(), source2->readData());
  dest->writeData(result);
}

/**
 *@brief
 * Template function to help launch i-instruction
 */
template <typename T>
void iTypeInstructionImmediate(std::shared_ptr<Register> dest,
                               T address_constant) {
  dest->writeData(address_constant);
}

/**
 *@brief
 * Template function to help launch j-instructions
 */
template <typename Op, typename T>
void jTypeInstruction(Op opFunc, T address) {
  opFunc(address);
}

/**
 * @brief The Instruction class
 * Instruction class acts as a decoded instruction. The CPU in this case
 * mainwindow only needs to read the corresponding pointers and data and call
 * operations from the ALU class.
 */
class Instruction {
 public:
  /**
   * @brief Instruction
   * Main constructor
   */
  Instruction() : m_opcode_(0x00), m_data_(0x00), m_data_type_(0x00){};

  /****SETTERS****/
  void setSource1(uint8_t source);
  void setSource2(uint8_t source);
  void setDestination(uint8_t source);
  void setOpType(OpTypes type);
  void setData(uint8_t data);

  /**
   * @brief setDataType
   * @param dataType
   * For future development, to include ints, floats etc.
   */
  void setDataType(uint8_t dataType);
  void setOpCode(uint8_t opcode);

  /****GETTERS****/
  uint8_t data() const;
  uint8_t source1() const;
  uint8_t source2() const;
  uint8_t destination() const;
  OpTypes optype() const { return m_type_; }
  uint8_t opcode() const { return m_opcode_; }

 private:
  uint8_t m_source1_;
  uint8_t m_source2_;
  uint8_t m_destination_;
  uint8_t m_opcode_;
  OpTypes m_type_;
  uint8_t m_data_;
  uint8_t m_data_type_;
};

using DecodedInstructions = QVector<isa::Instruction>;

/**********************************************************************/

}  // namespace isa

#endif  // LIB_ISA_INSTRUCTIONS_HPP_
