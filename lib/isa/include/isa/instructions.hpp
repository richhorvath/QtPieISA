#ifndef LIB_ISA_INSTRUCTIONS_HPP_
#define LIB_ISA_INSTRUCTIONS_HPP_

#include <QMap>
#include <QString>

/**********************************************************************/

enum class InstructionHex : uint64_t {
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

enum class OpTypes : uint8_t { R = 0x00, I, J };

/**********************************************************************/

#endif  // LIB_ISA_INSTRUCTIONS_HPP_
