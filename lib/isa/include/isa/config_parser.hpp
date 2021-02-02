#ifndef LIB_ISA_CONFIG_PARSER_HPP_
#define LIB_ISA_CONFIG_PARSER_HPP_
#include <QString>
#include <QtXml/QDomNode>
#include <vector>

class OpCode;

using InstVec = std::vector<OpCode>;

class ConfigParser {
 public:
  void parse(const QString &config_location, InstVec *inst_vec);
};

class OpCode {
 public:
  OpCode(const QDomNode &node);
  const QString &opCode() const { return m_op_code_; }
  uint8_t hexCode() const { return m_hex_code_; }

 private:
  QString m_op_code_;
  uint8_t m_hex_code_;
};
#endif  // LIB_ISA_CONFIG_PARSER_HPP_
