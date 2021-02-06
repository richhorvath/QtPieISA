#ifndef LIB_ISA_ALU_HPP_
#define LIB_ISA_ALU_HPP_

class ALU {
 public:
  /**
   * The following functors are classes used to pass in template types to
   * corresponding r type instruction.
   */
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
};

#endif  // LIB_ISA_ALU_HPP_
