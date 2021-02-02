#ifndef LIB_ISA_INSTRUCTIONS_HPP_
#define LIB_ISA_INSTRUCTIONS_HPP_

#include <QMap>
#include <QString>

#include "isa/register.hpp"

namespace isa {

/**********************************************************************/

/**********************************************************************/

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

enum class OpTypes : uint8_t { R = 0x00, IL, I, J };

/**********************************************************************/

template <typename T>
struct subtract {
  T operator()(T x, T y) { return x - y; }
};

/**********************************************************************/

template <typename T>
struct modulus {
  T operator()(T x, T y) { return x % y; }
};

/**********************************************************************/

template <typename T>
struct bitwiseAnd {
  T operator()(T x, T y) { return x | y; }
};

/**********************************************************************/

template <typename T>
struct add {
  T operator()(T x, T y) { return x + y; }
};

/**********************************************************************/

template <typename T>
struct divide {
  T operator()(T x, T y) { return x / y; }
};

/**********************************************************************/

template <typename T>
struct multiply {
  T operator()(T x, T y) { return x * y; }
};

/**********************************************************************/

/**
 *@brief
 * Template function to help launch rtype instructions.
 */
template <typename Op, typename T>
void rTypeInstruction(Register* source1, Op opFunc, Register* source2,
                      Register* dest) {
  auto result = opFunc(source1->readData(), source2->readData());
  dest->writeData(result);
}

/**
 *@brief
 * Template function to help launch i-instruction
 */
template <typename Op, typename T>
void iTypeInstruction(Register* source1, Op opFunc, T immediate,
                      Register* dest) {
  auto result = opFunc(source1->readData(), immediate);
  dest->writeData(result);
}

/**
 *@brief
 * Template function to help launch i-instruction
 */
template <typename Op, typename T>
void iTypeInstruction(Register* dest, Op opFunc, T address_constant) {
  auto result = opFunc(dest->readData(), address_constant);
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
 */
class Instruction {
 public:
  Instruction()
      : m_source1_(nullptr),
        m_source2_(nullptr),
        m_destination_(nullptr),
        m_opcode_(0x00),
        m_data_(0x00),
        m_data_type_(0x00){};

  void setSource1(Register* source);
  void setSource2(Register* source);
  void setDestination(Register* dest);
  void setOpType(OpTypes type);
  void setData(uint8_t data);
  void setDataType(uint8_t dataType);

  uint8_t data();
  Register* source1();
  Register* source2();
  Register* destination();

 private:
  Register* m_source1_;
  Register* m_source2_;
  Register* m_destination_;
  uint8_t m_opcode_;
  OpTypes m_type_;
  uint8_t m_data_;
  uint8_t m_data_type_;
};

/**********************************************************************/

}  // namespace isa

#endif  // LIB_ISA_INSTRUCTIONS_HPP_
