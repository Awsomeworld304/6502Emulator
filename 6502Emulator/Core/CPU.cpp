#include "CPU.h"
#include "Bus.h"
#include <iostream>
#include "../Utils/BetterConsole.h"

CPU::CPU()
{
	// ALL Instructions.
	// Mah lookup list.
	lookup =
	{
		{ "BRK", &CPU::BRK, &CPU::IMM, 7 },
		{ "ORA", &CPU::ORA, &CPU::IZX, 6 },
		{ "???", &CPU::IOP, &CPU::IMP, 2 },
		{ "???", &CPU::IOP, &CPU::IMP, 8 },
		{ "???", &CPU::NOP, &CPU::IMP, 3 },
		{ "ORA", &CPU::ORA, &CPU::ZP0, 3 },
		{ "ASL", &CPU::ASL, &CPU::ZP0, 5 },
		{ "???", &CPU::IOP, &CPU::IMP, 5 },
		{ "PHP", &CPU::PHP, &CPU::IMP, 3 },
		{ "ORA", &CPU::ORA, &CPU::IMM, 2 },
		{ "ASL", &CPU::ASL, &CPU::IMP, 2 },
		{ "???", &CPU::IOP, &CPU::IMP, 2 },
		{ "???", &CPU::NOP, &CPU::IMP, 4 },
		{ "ORA", &CPU::ORA, &CPU::ABS, 4 },
		{ "ASL", &CPU::ASL, &CPU::ABS, 6 },
		{ "???", &CPU::IOP, &CPU::IMP, 6 },
		{ "BPL", &CPU::BPL, &CPU::REL, 2 },
		{ "ORA", &CPU::ORA, &CPU::IZY, 5 },
		{ "???", &CPU::IOP, &CPU::IMP, 2 },
		{ "???", &CPU::IOP, &CPU::IMP, 8 },
		{ "???", &CPU::NOP, &CPU::IMP, 4 },
		{ "ORA", &CPU::ORA, &CPU::ZPX, 4 },
		{ "ASL", &CPU::ASL, &CPU::ZPX, 6 },
		{ "???", &CPU::IOP, &CPU::IMP, 6 },
		{ "CLC", &CPU::CLC, &CPU::IMP, 2 },
		{ "ORA", &CPU::ORA, &CPU::ABY, 4 },
		{ "???", &CPU::NOP, &CPU::IMP, 2 },
		{ "???", &CPU::IOP, &CPU::IMP, 7 },
		{ "???", &CPU::NOP, &CPU::IMP, 4 },
		{ "ORA", &CPU::ORA, &CPU::ABX, 4 },
		{ "ASL", &CPU::ASL, &CPU::ABX, 7 },
		{ "???", &CPU::IOP, &CPU::IMP, 7 },
		{ "JSR", &CPU::JSR, &CPU::ABS, 6 },
		{ "AND", &CPU::AND, &CPU::IZX, 6 },
		{ "???", &CPU::IOP, &CPU::IMP, 2 },
		{ "???", &CPU::IOP, &CPU::IMP, 8 },
		{ "BIT", &CPU::BIT, &CPU::ZP0, 3 },
		{ "AND", &CPU::AND, &CPU::ZP0, 3 },
		{ "ROL", &CPU::ROL, &CPU::ZP0, 5 },
		{ "???", &CPU::IOP, &CPU::IMP, 5 },
		{ "PLP", &CPU::PLP, &CPU::IMP, 4 },
		{ "AND", &CPU::AND, &CPU::IMM, 2 },
		{ "ROL", &CPU::ROL, &CPU::IMP, 2 },
		{ "???", &CPU::IOP, &CPU::IMP, 2 },
		{ "BIT", &CPU::BIT, &CPU::ABS, 4 },
		{ "AND", &CPU::AND, &CPU::ABS, 4 },
		{ "ROL", &CPU::ROL, &CPU::ABS, 6 },
		{ "???", &CPU::IOP, &CPU::IMP, 6 },
		{ "BMI", &CPU::BMI, &CPU::REL, 2 },
		{ "AND", &CPU::AND, &CPU::IZY, 5 },
		{ "???", &CPU::IOP, &CPU::IMP, 2 },
		{ "???", &CPU::IOP, &CPU::IMP, 8 },
		{ "???", &CPU::NOP, &CPU::IMP, 4 },
		{ "AND", &CPU::AND, &CPU::ZPX, 4 },
		{ "ROL", &CPU::ROL, &CPU::ZPX, 6 },
		{ "???", &CPU::IOP, &CPU::IMP, 6 },
		{ "SEC", &CPU::SEC, &CPU::IMP, 2 },
		{ "AND", &CPU::AND, &CPU::ABY, 4 },
		{ "???", &CPU::NOP, &CPU::IMP, 2 },
		{ "???", &CPU::IOP, &CPU::IMP, 7 },
		{ "???", &CPU::NOP, &CPU::IMP, 4 },
		{ "AND", &CPU::AND, &CPU::ABX, 4 },
		{ "ROL", &CPU::ROL, &CPU::ABX, 7 },
		{ "???", &CPU::IOP, &CPU::IMP, 7 },
		{ "RTI", &CPU::RTI, &CPU::IMP, 6 },
		{ "EOR", &CPU::EOR, &CPU::IZX, 6 },
		{ "???", &CPU::IOP, &CPU::IMP, 2 },
		{ "???", &CPU::IOP, &CPU::IMP, 8 },
		{ "???", &CPU::NOP, &CPU::IMP, 3 },
		{ "EOR", &CPU::EOR, &CPU::ZP0, 3 },
		{ "LSR", &CPU::LSR, &CPU::ZP0, 5 },
		{ "???", &CPU::IOP, &CPU::IMP, 5 },
		{ "PHA", &CPU::PHA, &CPU::IMP, 3 },
		{ "EOR", &CPU::EOR, &CPU::IMM, 2 },
		{ "LSR", &CPU::LSR, &CPU::IMP, 2 },
		{ "???", &CPU::IOP, &CPU::IMP, 2 },
		{ "JMP", &CPU::JMP, &CPU::ABS, 3 },
		{ "EOR", &CPU::EOR, &CPU::ABS, 4 },
		{ "LSR", &CPU::LSR, &CPU::ABS, 6 },
		{ "???", &CPU::IOP, &CPU::IMP, 6 },
		{ "BVC", &CPU::BVC, &CPU::REL, 2 },
		{ "EOR", &CPU::EOR, &CPU::IZY, 5 },
		{ "???", &CPU::IOP, &CPU::IMP, 2 },
		{ "???", &CPU::IOP, &CPU::IMP, 8 },
		{ "???", &CPU::NOP, &CPU::IMP, 4 },
		{ "EOR", &CPU::EOR, &CPU::ZPX, 4 },
		{ "LSR", &CPU::LSR, &CPU::ZPX, 6 },
		{ "???", &CPU::IOP, &CPU::IMP, 6 },
		{ "CLI", &CPU::CLI, &CPU::IMP, 2 },
		{ "EOR", &CPU::EOR, &CPU::ABY, 4 },
		{ "???", &CPU::NOP, &CPU::IMP, 2 },
		{ "???", &CPU::IOP, &CPU::IMP, 7 },
		{ "???", &CPU::NOP, &CPU::IMP, 4 },
		{ "EOR", &CPU::EOR, &CPU::ABX, 4 },
		{ "LSR", &CPU::LSR, &CPU::ABX, 7 },
		{ "???", &CPU::IOP, &CPU::IMP, 7 },
		{ "RTS", &CPU::RTS, &CPU::IMP, 6 },
		{ "ADC", &CPU::ADC, &CPU::IZX, 6 },
		{ "???", &CPU::IOP, &CPU::IMP, 2 },
		{ "???", &CPU::IOP, &CPU::IMP, 8 },
		{ "???", &CPU::NOP, &CPU::IMP, 3 },
		{ "ADC", &CPU::ADC, &CPU::ZP0, 3 },
		{ "ROR", &CPU::ROR, &CPU::ZP0, 5 },
		{ "???", &CPU::IOP, &CPU::IMP, 5 },
		{ "PLA", &CPU::PLA, &CPU::IMP, 4 },
		{ "ADC", &CPU::ADC, &CPU::IMM, 2 },
		{ "ROR", &CPU::ROR, &CPU::IMP, 2 },
		{ "???", &CPU::IOP, &CPU::IMP, 2 },
		{ "JMP", &CPU::JMP, &CPU::IND, 5 },
		{ "ADC", &CPU::ADC, &CPU::ABS, 4 },
		{ "ROR", &CPU::ROR, &CPU::ABS, 6 },
		{ "???", &CPU::IOP, &CPU::IMP, 6 },
		{ "BVS", &CPU::BVS, &CPU::REL, 2 },
		{ "ADC", &CPU::ADC, &CPU::IZY, 5 },
		{ "???", &CPU::IOP, &CPU::IMP, 2 },
		{ "???", &CPU::IOP, &CPU::IMP, 8 },
		{ "???", &CPU::NOP, &CPU::IMP, 4 },
		{ "ADC", &CPU::ADC, &CPU::ZPX, 4 },
		{ "ROR", &CPU::ROR, &CPU::ZPX, 6 },
		{ "???", &CPU::IOP, &CPU::IMP, 6 },
		{ "SEI", &CPU::SEI, &CPU::IMP, 2 },
		{ "ADC", &CPU::ADC, &CPU::ABY, 4 },
		{ "???", &CPU::NOP, &CPU::IMP, 2 },
		{ "???", &CPU::IOP, &CPU::IMP, 7 },
		{ "???", &CPU::NOP, &CPU::IMP, 4 },
		{ "ADC", &CPU::ADC, &CPU::ABX, 4 },
		{ "ROR", &CPU::ROR, &CPU::ABX, 7 },
		{ "???", &CPU::IOP, &CPU::IMP, 7 },
		{ "???", &CPU::NOP, &CPU::IMP, 2 },
		{ "STA", &CPU::STA, &CPU::IZX, 6 },
		{ "???", &CPU::NOP, &CPU::IMP, 2 },
		{ "???", &CPU::IOP, &CPU::IMP, 6 },
		{ "STY", &CPU::STY, &CPU::ZP0, 3 },
		{ "STA", &CPU::STA, &CPU::ZP0, 3 },
		{ "STX", &CPU::STX, &CPU::ZP0, 3 },
		{ "???", &CPU::IOP, &CPU::IMP, 3 },
		{ "DEY", &CPU::DEY, &CPU::IMP, 2 },
		{ "???", &CPU::NOP, &CPU::IMP, 2 },
		{ "TXA", &CPU::TXA, &CPU::IMP, 2 },
		{ "???", &CPU::IOP, &CPU::IMP, 2 },
		{ "STY", &CPU::STY, &CPU::ABS, 4 },
		{ "STA", &CPU::STA, &CPU::ABS, 4 },
		{ "STX", &CPU::STX, &CPU::ABS, 4 },
		{ "???", &CPU::IOP, &CPU::IMP, 4 },
		{ "BCC", &CPU::BCC, &CPU::REL, 2 },
		{ "STA", &CPU::STA, &CPU::IZY, 6 },
		{ "???", &CPU::IOP, &CPU::IMP, 2 },
		{ "???", &CPU::IOP, &CPU::IMP, 6 },
		{ "STY", &CPU::STY, &CPU::ZPX, 4 },
		{ "STA", &CPU::STA, &CPU::ZPX, 4 },
		{ "STX", &CPU::STX, &CPU::ZPY, 4 },
		{ "???", &CPU::IOP, &CPU::IMP, 4 },
		{ "TYA", &CPU::TYA, &CPU::IMP, 2 },
		{ "STA", &CPU::STA, &CPU::ABY, 5 },
		{ "TXS", &CPU::TXS, &CPU::IMP, 2 },
		{ "???", &CPU::IOP, &CPU::IMP, 5 },
		{ "???", &CPU::NOP, &CPU::IMP, 5 },
		{ "STA", &CPU::STA, &CPU::ABX, 5 },
		{ "???", &CPU::IOP, &CPU::IMP, 5 },
		{ "???", &CPU::IOP, &CPU::IMP, 5 },
		{ "LDY", &CPU::LDY, &CPU::IMM, 2 },
		{ "LDA", &CPU::LDA, &CPU::IZX, 6 },
		{ "LDX", &CPU::LDX, &CPU::IMM, 2 },
		{ "???", &CPU::IOP, &CPU::IMP, 6 },
		{ "LDY", &CPU::LDY, &CPU::ZP0, 3 },
		{ "LDA", &CPU::LDA, &CPU::ZP0, 3 },
		{ "LDX", &CPU::LDX, &CPU::ZP0, 3 },
		{ "???", &CPU::IOP, &CPU::IMP, 3 },
		{ "TAY", &CPU::TAY, &CPU::IMP, 2 },
		{ "LDA", &CPU::LDA, &CPU::IMM, 2 },
		{ "TAX", &CPU::TAX, &CPU::IMP, 2 },
		{ "???", &CPU::IOP, &CPU::IMP, 2 },
		{ "LDY", &CPU::LDY, &CPU::ABS, 4 },
		{ "LDA", &CPU::LDA, &CPU::ABS, 4 },
		{ "LDX", &CPU::LDX, &CPU::ABS, 4 },
		{ "???", &CPU::IOP, &CPU::IMP, 4 },
		{ "BCS", &CPU::BCS, &CPU::REL, 2 },
		{ "LDA", &CPU::LDA, &CPU::IZY, 5 },
		{ "???", &CPU::IOP, &CPU::IMP, 2 },
		{ "???", &CPU::IOP, &CPU::IMP, 5 },
		{ "LDY", &CPU::LDY, &CPU::ZPX, 4 },
		{ "LDA", &CPU::LDA, &CPU::ZPX, 4 },
		{ "LDX", &CPU::LDX, &CPU::ZPY, 4 },
		{ "???", &CPU::IOP, &CPU::IMP, 4 },
		{ "CLV", &CPU::CLV, &CPU::IMP, 2 },
		{ "LDA", &CPU::LDA, &CPU::ABY, 4 },
		{ "TSX", &CPU::TSX, &CPU::IMP, 2 },
		{ "???", &CPU::IOP, &CPU::IMP, 4 },
		{ "LDY", &CPU::LDY, &CPU::ABX, 4 },
		{ "LDA", &CPU::LDA, &CPU::ABX, 4 },
		{ "LDX", &CPU::LDX, &CPU::ABY, 4 },
		{ "???", &CPU::IOP, &CPU::IMP, 4 },
		{ "CPY", &CPU::CPY, &CPU::IMM, 2 },
		{ "CMP", &CPU::CMP, &CPU::IZX, 6 },
		{ "???", &CPU::NOP, &CPU::IMP, 2 },
		{ "???", &CPU::IOP, &CPU::IMP, 8 },
		{ "CPY", &CPU::CPY, &CPU::ZP0, 3 },
		{ "CMP", &CPU::CMP, &CPU::ZP0, 3 },
		{ "DEC", &CPU::DEC, &CPU::ZP0, 5 },
		{ "???", &CPU::IOP, &CPU::IMP, 5 },
		{ "INY", &CPU::INY, &CPU::IMP, 2 },
		{ "CMP", &CPU::CMP, &CPU::IMM, 2 },
		{ "DEX", &CPU::DEX, &CPU::IMP, 2 },
		{ "???", &CPU::IOP, &CPU::IMP, 2 },
		{ "CPY", &CPU::CPY, &CPU::ABS, 4 },
		{ "CMP", &CPU::CMP, &CPU::ABS, 4 },
		{ "DEC", &CPU::DEC, &CPU::ABS, 6 },
		{ "???", &CPU::IOP, &CPU::IMP, 6 },
		{ "BNE", &CPU::BNE, &CPU::REL, 2 },
		{ "CMP", &CPU::CMP, &CPU::IZY, 5 },
		{ "???", &CPU::IOP, &CPU::IMP, 2 },
		{ "???", &CPU::IOP, &CPU::IMP, 8 },
		{ "???", &CPU::NOP, &CPU::IMP, 4 },
		{ "CMP", &CPU::CMP, &CPU::ZPX, 4 },
		{ "DEC", &CPU::DEC, &CPU::ZPX, 6 },
		{ "???", &CPU::IOP, &CPU::IMP, 6 },
		{ "CLD", &CPU::CLD, &CPU::IMP, 2 },
		{ "CMP", &CPU::CMP, &CPU::ABY, 4 },
		{ "NOP", &CPU::NOP, &CPU::IMP, 2 },
		{ "???", &CPU::IOP, &CPU::IMP, 7 },
		{ "???", &CPU::NOP, &CPU::IMP, 4 },
		{ "CMP", &CPU::CMP, &CPU::ABX, 4 },
		{ "DEC", &CPU::DEC, &CPU::ABX, 7 },
		{ "???", &CPU::IOP, &CPU::IMP, 7 },
		{ "CPX", &CPU::CPX, &CPU::IMM, 2 },
		{ "SBC", &CPU::SBC, &CPU::IZX, 6 },
		{ "???", &CPU::NOP, &CPU::IMP, 2 },
		{ "???", &CPU::IOP, &CPU::IMP, 8 },
		{ "CPX", &CPU::CPX, &CPU::ZP0, 3 },
		{ "SBC", &CPU::SBC, &CPU::ZP0, 3 },
		{ "INC", &CPU::INC, &CPU::ZP0, 5 },
		{ "???", &CPU::IOP, &CPU::IMP, 5 },
		{ "INX", &CPU::INX, &CPU::IMP, 2 },
		{ "SBC", &CPU::SBC, &CPU::IMM, 2 },
		{ "NOP", &CPU::NOP, &CPU::IMP, 2 },
		{ "???", &CPU::SBC, &CPU::IMP, 2 },
		{ "CPX", &CPU::CPX, &CPU::ABS, 4 },
		{ "SBC", &CPU::SBC, &CPU::ABS, 4 },
		{ "INC", &CPU::INC, &CPU::ABS, 6 },
		{ "???", &CPU::IOP, &CPU::IMP, 6 },
		{ "BEQ", &CPU::BEQ, &CPU::REL, 2 },
		{ "SBC", &CPU::SBC, &CPU::IZY, 5 },
		{ "???", &CPU::IOP, &CPU::IMP, 2 },
		{ "???", &CPU::IOP, &CPU::IMP, 8 },
		{ "???", &CPU::NOP, &CPU::IMP, 4 },
		{ "SBC", &CPU::SBC, &CPU::ZPX, 4 },
		{ "INC", &CPU::INC, &CPU::ZPX, 6 },
		{ "???", &CPU::IOP, &CPU::IMP, 6 },
		{ "SED", &CPU::SED, &CPU::IMP, 2 },
		{ "SBC", &CPU::SBC, &CPU::ABY, 4 },
		{ "NOP", &CPU::NOP, &CPU::IMP, 2 },
		{ "???", &CPU::IOP, &CPU::IMP, 7 },
		{ "???", &CPU::NOP, &CPU::IMP, 4 },
		{ "SBC", &CPU::SBC, &CPU::ABX, 4 },
		{ "INC", &CPU::INC, &CPU::ABX, 7 },
		{ "???", &CPU::IOP, &CPU::IMP, 7 },
	};
}

CPU::~CPU()
{
	// Literally do nothing dumbass.
}

/**
	Read from the bus.
	@return Data from requested address.
*/
uint8_t CPU::read(uint16_t a)
{
	BetterConsole::Log("[CPU] Requested Address from Bus: " + a);
	return bus->read(a, false);
}

/** 
	Write to the bus. 
	@param a - The address to write to.
	@param d - The data to write.
*/
void CPU::write(uint16_t a, uint8_t d) 
{
	bus->write(a, d);
}

/** 
	Resets the CPU back to a known state.
	Requires eight cycles to complete.
*/
void CPU::reset()
{
	addr_abs = 0xFFFC;
	uint16_t lo = read(addr_abs + 0);
	uint16_t hi = read(addr_abs + 1);

	pc = (hi << 8) | lo;

	a = 0;
	x = 0;
	y = 0;
	stkp = 0xFD;
	status = 0x00 | U;

	addr_rel = 0x0000;
	addr_abs = 0x0000;
	fetched = 0x00;

	cycles = 8;
}

/**
	Interrupt Request.
	Requires seven cycles to complete.
*/
void CPU::irq() 
{
	if (GetFlag(I) == 0)
	{
		write(0x0100 + stkp, (pc >> 8) & 0x00FF);
		stkp--;
		write(0x0100 + stkp, pc & 0x00FF);
		stkp--;

		SetFlag(B, 0);
		SetFlag(U, 1);
		SetFlag(I, 1);
		write(0x0100 + stkp, status);
		stkp--;

		addr_abs = 0xFFFE;
		uint16_t lo = read(addr_abs + 0);
		uint16_t hi = read(addr_abs + 1);
		pc = (hi << 8) | lo;

		cycles = 7;
	}
}

/**
	Non-Maskable Interrupt.
	Requires eight cycles to complete.
*/
void CPU::nmi()
{
	write(0x0100 + stkp, (pc >> 8) & 0x00FF);
	stkp--;
	write(0x0100 + stkp, pc & 0x00FF);
	stkp--;

	SetFlag(B, 0);
	SetFlag(U, 1);
	SetFlag(I, 1);
	write(0x0100 + stkp, status);
	stkp--;

	addr_abs = 0xFFFA;
	uint16_t lo = read(addr_abs + 0);
	uint16_t hi = read(addr_abs + 1);
	pc = (hi << 8) | lo;

	cycles = 8;
}

/**
	Preform one clock cycle of the CPU.
*/
void CPU::clock()
{
	if (cycles == 0)
	{
		opcode = read(pc);
		uint16_t log_pc = pc;
		SetFlag(U, true);
		pc++;

		cycles = lookup[opcode].cycles;
		uint8_t additional_cycle1 = (this->*lookup[opcode].addrmode)();
		uint8_t additional_cycle2 = (this->*lookup[opcode].operate)();

		cycles += (additional_cycle1 & additional_cycle2);
		SetFlag(U, true);
	}

	cycles--;
	clock_count++;
}

bool CPU::complete()
{
	if (cycles == 0)
		return true;

	return false;
}

uint8_t CPU::GetFlag(Flags f) const
{
	return ((status & f) > 0) ? 1 : 0;
}

void CPU::SetFlag(Flags f, bool v)
{
	if (v)
		status |= f;
	else
		status &= ~f;
}

uint8_t CPU::fetch()
{
	if (!(lookup[opcode].addrmode == &CPU::IMP))
		fetched = read(addr_abs);
	return fetched;
}

uint8_t CPU::IMP()
{
	fetched = a;
	return 0;
}

uint8_t CPU::IMM()
{
	addr_abs = pc++;
	return 0;
}

uint8_t CPU::ZP0()
{
	addr_abs = read(pc);
	pc++;
	addr_abs &= 0x00FF;
	return 0;
}

uint8_t CPU::ZPX()
{
	addr_abs = (read(pc) + x);
	pc++;
	addr_abs &= 0x00FF;
	return 0;
}

uint8_t CPU::ZPY()
{
	addr_abs = (read(pc) + y);
	pc++;
	addr_abs &= 0x00FF;
	return 0;
}

uint8_t CPU::REL()
{
	addr_rel = read(pc);
	pc++;
	if (addr_rel & 0x80)
		addr_rel |= 0xFF00;
	return 0;
}

uint8_t CPU::ABS()
{
	uint16_t lo = read(pc);
	pc++;
	uint16_t hi = read(pc);
	pc++;

	addr_abs = (hi << 8) | lo;
	return 0;
}

uint8_t CPU::ABX()
{
	uint16_t lo = read(pc);
	pc++;
	uint16_t hi = read(pc);
	pc++;

	addr_abs = (hi << 8) | lo;
	addr_abs += x;

	if ((addr_abs & 0xFF00) != (hi << 8))
		return 1;
	else
		return 0;
}

uint8_t CPU::ABY()
{
	uint16_t lo = read(pc);
	pc++;
	uint16_t hi = read(pc);
	pc++;

	addr_abs = (hi << 8) | lo;
	addr_abs += y;

	if ((addr_abs & 0xFF00) != (hi << 8))
		return 1;
	else
		return 0;
}

uint8_t CPU::IND()
{
	uint16_t ptr_lo = read(pc);
	pc++;
	uint16_t ptr_hi = read(pc);
	pc++;

	uint16_t ptr = (ptr_hi << 8) | ptr_lo;

	if (ptr_lo == 0x00FF)
		addr_abs = (read(ptr & 0xFF00) << 8) | read(ptr + 0);
	else
		addr_abs = (read(ptr + 1) << 8) | read(ptr + 0);

	return 0;
}

uint8_t CPU::IZX()
{
	uint16_t t = read(pc);
	pc++;

	uint16_t lo = read((uint16_t)(t + (uint16_t)x) & 0x00FF);
	uint16_t hi = read((uint16_t)(t + (uint16_t)x + 1) & 0x00FF);

	addr_abs = (hi << 8) | lo;

	return 0;
}

uint8_t CPU::IZY()
{
	uint16_t t = read(pc);
	pc++;

	uint16_t lo = read(t & 0x00FF);
	uint16_t hi = read((t + 1) & 0x00FF);

	addr_abs = (hi << 8) | lo;
	addr_abs += y;

	if ((addr_abs & 0xFF00) != (hi << 8))
		return 1;
	else
		return 0;
}

// Illegal Opcode Placeholder
uint8_t CPU::IOP()
{
	std::cout << "[CPU] Illegal Opcode requested." << std::endl;
	return 0;
}

uint8_t CPU::ADC()
{
	fetch();
	uint16_t temp = (uint16_t)a + (uint16_t)fetched + (uint16_t)GetFlag(C);

	SetFlag(C, temp > 255);
	SetFlag(Z, (temp & 0x00FF) == 0);
	SetFlag(N, temp & 0x80);
	SetFlag(V, (~(uint16_t)a ^ (uint16_t)fetched) & ((uint16_t)a ^ (uint16_t)temp) & 0x0080);

	a = temp & 0x00FF;
	return 1;
}

uint8_t CPU::AND()
{
	fetch();
	a = a & fetched;
	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);
	return 1;
}

uint8_t CPU::ASL()
{
	fetch();
	uint16_t temp = (uint16_t)fetched << 1;
	SetFlag(C, (temp & 0xFF00) > 0);
	SetFlag(Z, (temp & 0x00FF) == 0x00);
	SetFlag(N, temp & 0x80);
	if (lookup[opcode].addrmode == &CPU::IMP)
		a = temp & 0x00FF;
	else
		write(addr_abs, temp & 0x00FF);
	return 0;
}

uint8_t CPU::BCC()
{
	if (GetFlag(C) == 0)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}

uint8_t CPU::BCS()
{
	if (GetFlag(C) == 1)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}

uint8_t CPU::BEQ()
{
	if (GetFlag(Z) == 1)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}

uint8_t CPU::BIT()
{
	fetch();
	uint16_t temp = a & fetched;
	SetFlag(Z, (temp & 0x00FF) == 0x00);
	SetFlag(N, fetched & (1 << 7));
	SetFlag(V, fetched & (1 << 6));
	return 0;
}

uint8_t CPU::BMI()
{
	if (GetFlag(N) == 1)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}

uint8_t CPU::BNE()
{
	if (GetFlag(Z) == 0)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}

uint8_t CPU::BPL()
{
	if (GetFlag(N) == 0)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}

uint8_t CPU::BRK()
{
	pc++;

	SetFlag(I, 1);
	write(0x0100 + stkp, (pc >> 8) & 0x00FF);
	stkp--;
	write(0x0100 + stkp, pc & 0x00FF);
	stkp--;

	SetFlag(B, 1);
	write(0x0100 + stkp, status);
	stkp--;
	SetFlag(B, 0);

	addr_abs = 0xFFFE;
	uint16_t lo = read(addr_abs + 0);
	uint16_t hi = read(addr_abs + 1);
	pc = (hi << 8) | lo;

	return 0;
}

uint8_t CPU::BVC()
{
	if (GetFlag(V) == 0)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}

uint8_t CPU::BVS()
{
	if (GetFlag(V) == 1)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}

uint8_t CPU::CLC()
{
	SetFlag(C, false);
	return 0;
}

uint8_t CPU::CLD()
{
	SetFlag(D, false);
	return 0;
}

uint8_t CPU::CLI()
{
	SetFlag(I, false);
	return 0;
}

uint8_t CPU::CLV()
{
	SetFlag(V, false);
	return 0;
}

uint8_t CPU::CMP()
{
	fetch();
	uint16_t temp = (uint16_t)a - (uint16_t)fetched;
	SetFlag(C, a >= fetched);
	SetFlag(Z, (temp & 0x00FF) == 0x0000);
	SetFlag(N, temp & 0x0080);
	return 1;
}

uint8_t CPU::CPX()
{
	fetch();
	uint16_t temp = (uint16_t)x - (uint16_t)fetched;
	SetFlag(C, x >= fetched);
	SetFlag(Z, (temp & 0x00FF) == 0x0000);
	SetFlag(N, temp & 0x0080);
	return 1;
}

uint8_t CPU::CPY()
{
	fetch();
	uint16_t temp = (uint16_t)y - (uint16_t)fetched;
	SetFlag(C, y >= fetched);
	SetFlag(Z, (temp & 0x00FF) == 0x0000);
	SetFlag(N, temp & 0x0080);
	return 1;
}

uint8_t CPU::DEC()
{
	fetch();
	uint16_t temp = fetched - 1;
	write(addr_abs, temp & 0x00FF);
	SetFlag(Z, (temp & 0x00FF) == 0x0000);
	SetFlag(N, temp & 0x0080);
	return 0;
}

uint8_t CPU::DEX()
{
	x--;
	SetFlag(Z, x == 0x00);
	SetFlag(N, x & 0x80);
	return 0;
}

uint8_t CPU::DEY()
{
	y--;
	SetFlag(Z, y == 0x00);
	SetFlag(N, y & 0x80);
	return 0;
}

uint8_t CPU::EOR()
{
	fetch();
	a = a ^ fetched;
	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);
	return 1;
}

uint8_t CPU::INC()
{
	fetch();
	uint16_t temp = fetched + 1;
	write(addr_abs, temp & 0x00FF);
	SetFlag(Z, (temp & 0x00FF) == 0x0000);
	SetFlag(N, temp & 0x0080);
	return 0;
}

uint8_t CPU::INX()
{
	x++;
	SetFlag(Z, x == 0x00);
	SetFlag(N, x & 0x80);
	return 0;
}

uint8_t CPU::INY()
{
	y++;
	SetFlag(Z, y == 0x00);
	SetFlag(N, y & 0x80);
	return 0;
}

uint8_t CPU::JMP()
{
	pc = addr_abs;
	return 0;
}

uint8_t CPU::JSR()
{
	pc--;

	write(0x0100 + stkp, (pc >> 8) & 0x00FF);
	stkp--;
	write(0x0100 + stkp, pc & 0x00FF);
	stkp--;

	pc = addr_abs;
	return 0;
}

uint8_t CPU::LDA()
{
	fetch();
	a = fetched;
	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);
	return 1;
}

uint8_t CPU::LDX()
{
	fetch();
	x = fetched;
	SetFlag(Z, x == 0x00);
	SetFlag(N, x & 0x80);
	return 1;
}

uint8_t CPU::LDY()
{
	fetch();
	y = fetched;
	SetFlag(Z, y == 0x00);
	SetFlag(N, y & 0x80);
	return 1;
}

uint8_t CPU::LSR()
{
	fetch();
	SetFlag(C, fetched & 0x0001);
	uint16_t temp = fetched >> 1;
	SetFlag(Z, (temp & 0x00FF) == 0x0000);
	SetFlag(N, temp & 0x0080);
	if (lookup[opcode].addrmode == &CPU::IMP)
		a = temp & 0x00FF;
	else
		write(addr_abs, temp & 0x00FF);
	return 0;
}

uint8_t CPU::NOP()
{
	return 0;
}

uint8_t CPU::ORA()
{
	fetch();
	a = a | fetched;
	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);
	return 1;
}

uint8_t CPU::PHA()
{
	write(0x0100 + stkp, a);
	stkp--;
	return 0;
}

uint8_t CPU::PHP()
{
	write(0x0100 + stkp, status | B | U);
	SetFlag(B, 0);
	SetFlag(U, 0);
	stkp--;
	return 0;
}

uint8_t CPU::PLA()
{
	stkp++;
	a = read(0x0100 + stkp);
	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);
	return 0;
}

uint8_t CPU::PLP()
{
	stkp++;
	status = read(0x0100 + stkp);
	SetFlag(U, 1);
	return 0;
}

uint8_t CPU::ROL()
{
	fetch();
	uint16_t temp = (uint16_t)(fetched << 1) | GetFlag(C);
	SetFlag(C, temp & 0xFF00);
	SetFlag(Z, (temp & 0x00FF) == 0x0000);
	SetFlag(N, temp & 0x0080);
	if (lookup[opcode].addrmode == &CPU::IMP)
		a = temp & 0x00FF;
	else
		write(addr_abs, temp & 0x00FF);
	return 0;
}

uint8_t CPU::ROR()
{
	fetch();
	uint16_t temp = (uint16_t)(GetFlag(C) << 7) | (fetched >> 1);
	SetFlag(C, fetched & 0x01);
	SetFlag(Z, (temp & 0x00FF) == 0x0000);
	SetFlag(N, temp & 0x0080);
	if (lookup[opcode].addrmode == &CPU::IMP)
		a = temp & 0x00FF;
	else
		write(addr_abs, temp & 0x00FF);
	return 0;
}

uint8_t CPU::RTI()
{
	stkp++;
	status = read(0x0100 + stkp);
	status &= ~B;
	status &= ~U;

	stkp++;
	uint16_t lo = read(0x0100 + stkp);
	stkp++;
	uint16_t hi = read(0x0100 + stkp);

	pc = (hi << 8) | lo;
	return 0;
}

uint8_t CPU::RTS()
{
	stkp++;
	uint16_t lo = read(0x0100 + stkp);
	stkp++;
	uint16_t hi = read(0x0100 + stkp);

	pc = ((hi << 8) | lo) + 1;
	return 0;
}

uint8_t CPU::SBC()
{
	fetch();
	uint16_t value = (uint16_t)fetched ^ 0x00FF;
	uint16_t temp = (uint16_t)a + value + (uint16_t)GetFlag(C);

	SetFlag(C, temp & 0xFF00);
	SetFlag(Z, (temp & 0x00FF) == 0);
	SetFlag(N, temp & 0x0080);
	SetFlag(V, (temp ^ (uint16_t)a) & (temp ^ value) & 0x0080);

	a = temp & 0x00FF;
	return 1;
}

uint8_t CPU::SEC()
{
	SetFlag(C, true);
	return 0;
}

uint8_t CPU::SED()
{
	SetFlag(D, true);
	return 0;
}

uint8_t CPU::SEI()
{
	SetFlag(I, true);
	return 0;
}

uint8_t CPU::STA()
{
	write(addr_abs, a);
	return 0;
}

uint8_t CPU::STX()
{
	write(addr_abs, x);
	return 0;
}

uint8_t CPU::STY()
{
	write(addr_abs, y);
	return 0;
}

uint8_t CPU::TAX()
{
	x = a;
	SetFlag(Z, x == 0x00);
	SetFlag(N, x & 0x80);
	return 0;
}

uint8_t CPU::TAY()
{
	y = a;
	SetFlag(Z, y == 0x00);
	SetFlag(N, y & 0x80);
	return 0;
}

uint8_t CPU::TSX()
{
	x = stkp;
	SetFlag(Z, x == 0x00);
	SetFlag(N, x & 0x80);
	return 0;
}

uint8_t CPU::TXA()
{
	a = x;
	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);
	return 0;
}

uint8_t CPU::TXS()
{
	stkp = x;
	return 0;
}

uint8_t CPU::TYA()
{
	a = y;
	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);
	return 0;
}