#ifndef LIB_ISA_REGISTER_HPP_
#define LIB_ISA_REGISTER_HPP_

#include <cstdint>
/**
 * @brief The Register class
 */
class Register {
 public:
  /**
   * @brief Register
   */
  Register(){};

  /**
   * @brief Register
   * @param data
   */
  explicit Register(const uint8_t& data) : m_data_(data) {}

  /**
   * @brief writeData
   * @param data
   */
  void writeData(const uint8_t& data) { m_data_ = data; };

  /**
   * @brief setNegative
   * @param is_negative
   */
  void setNegative(bool is_negative) { m_negative_ = is_negative; }

  /**
   * @brief setInteger
   * @param is_integer
   */
  void setInteger(bool is_integer) { m_integer_ = is_integer; }

  /**
   * @brief setFloat
   * @param is_float
   */
  void setFloat(bool is_float) { m_float_ = is_float; }

  /**
   * @brief readData
   * @param data
   */
  const uint8_t& readData() { return m_data_; };

 private:
  uint8_t m_data_{0x00};
  bool m_negative_{false};
  bool m_integer_{false};
  bool m_float_{false};
};

#endif  // LIB_ISA_REGISTER_HPP_
