#ifndef LIB_ISA_CONFIG_PARSER_HPP_
#define LIB_ISA_CONFIG_PARSER_HPP_
#include <QString>
#include <QtXml/QDomNode>
#include <vector>

class Token;
class Register;
class Instruction;

using InstVec = std::vector<Instruction>;

class ConfigParser {
 public:
  void parse(const QString &config_location, InstVec *inst_vec);
};

class Instruction {
 public:
  Instruction(const QDomNode &node);
  const QString &opCode() const { return m_op_code_; }
  uint64_t hexCode() const { return m_hex_code_; }

 private:
  QString m_op_code_;
  uint64_t m_hex_code_;
};
#endif  // LIB_ISA_CONFIG_PARSER_HPP_
