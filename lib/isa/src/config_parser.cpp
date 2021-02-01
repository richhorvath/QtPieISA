#include "isa/config_parser.hpp"

#include <QDebug>
#include <QFile>
#include <QtXml/QDomDocument>

void ConfigParser::parse(const QString &config_location, InstVec *inst_vec) {
  QDomDocument doc("isa_config");
  QFile file(config_location);
  if (!file.open(QIODevice::ReadOnly)) return;
  if (!doc.setContent(&file)) {
    file.close();
    return;
  }
  file.close();

  QDomElement docElem = doc.documentElement();
  QDomNode n = docElem.firstChild();

  while (!n.isNull()) {
    QDomElement e = n.toElement();  // try to convert the node to an element.
    if (!e.isNull()) {
      Instruction inst(n);
      inst_vec->push_back(inst);
    }
    n = n.nextSibling();
  }
}

Instruction::Instruction(const QDomNode &node)
    : m_op_code_(node.attributes().namedItem("Op_Code").nodeValue()) {
  bool ok = true;
  m_hex_code_ = node.attributes()
                    .namedItem("Hex_Representation")
                    .nodeValue()
                    .toUInt(&ok, 16);
}
