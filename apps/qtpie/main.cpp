#include <QApplication>

#include "isa/config_parser.hpp"
#include "isa/mainwindow.hpp"
int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QCoreApplication::setOrganizationName("QtPie");
  QCoreApplication::setApplicationName("QtPie ISA");

  ConfigParser parser;
  InstVec inst_vec;
  parser.parse("../config/isa_config.xml", &inst_vec);

  MainWindow window(inst_vec);
  window.show();
  return app.exec();
}
