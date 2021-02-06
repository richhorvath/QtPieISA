#ifndef LIB_ISA_MAINWINDOW_HPP_
#define LIB_ISA_MAINWINDOW_HPP_

#include <QMainWindow>
#include <QStandardItemModel>
#include <memory>

#include "isa/config_parser.hpp"
#include "isa/decoder.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  /**
   * @brief MainWindow
   * @param inst_vec
   * @param parent
   * The main constructor for the application. Sets up UI, registers, memory and
   * connects execute button to slot.
   */
  explicit MainWindow(const InstVec &inst_vec, QWidget *parent = nullptr);
  //! Destructor, deletes and clears list of registers. Deletes UI.
  ~MainWindow();

 private:
  /**
   * @brief slot_onExecute
   * Call back for when button gets executed, sends the string from the terminal
   * into the decoder clears all data then executes the instructions based on
   * decoded instructions. calls updatetables.
   */
  void slot_onExecute();
  /**
   * @brief toHexString
   * @param hex
   * @return
   * Translates hex values to prefixed 0x hex syntax.
   */
  QString toHexString(uint8_t hex);

  /**
   * @brief updateTables
   * Iterates through both tables updating data from registers and memory
   * vectors.
   */
  void updateTables();

  /**
   * @brief clearData
   * Clears all tables and vectors by iteration
   */
  void clearData();

  /**
   * @brief setupRegisters
   * Iterates over registers and register tables inserting 0x00
   */
  void setupRegisters();

  /**
   * @brief setupMemory
   * Iterates over memory and memory tables inserting 0x00
   */
  void setupMemory();

  Ui::MainWindow *m_ui_;
  InstructionDecoder *m_decoder_;
  QVector<std::shared_ptr<Register>> m_registers_;
  QStandardItemModel *m_reg_table_;
  QStandardItemModel *m_mem_table_;
  QVector<uint8_t> m_memory_;
};

#endif  // LIB_ISA_MAINWINDOW_HPP_
