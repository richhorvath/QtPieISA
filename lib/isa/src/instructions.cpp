#include "isa/instructions.hpp"
using namespace isa;
void Instruction::setSource1(Register* source) { m_source1_ = source; }
void Instruction::setSource2(Register* source) { m_source2_ = source; }
void Instruction::setDestination(Register* dest) { m_destination_ = dest; }
void Instruction::setOpType(OpTypes type) { m_type_ = type; }
void Instruction::setData(uint8_t data) { m_data_ = data; }
void Instruction::setDataType(uint8_t dataType) { m_data_type_ = dataType; }
void Instruction::setOpCode(uint8_t opcode) { m_opcode_ = opcode; }
uint8_t Instruction::data() const { return m_data_; }
Register* Instruction::source1() const { return m_source1_; }
Register* Instruction::source2() const { return m_source2_; }
Register* Instruction::destination() const { return m_destination_; }
