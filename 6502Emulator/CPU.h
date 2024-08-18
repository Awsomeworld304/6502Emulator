#pragma once
#include <cstdint>
#include <array>
#include <vector>
#include <string>
#include <map>

class Bus;

class CPU
{
	public:
		CPU();
		~CPU();
	public:
		uint8_t a = 0x00; // Accumulator Register
		uint8_t x = 0x00; // 'X Register
		uint8_t y = 0x00; // Y Register
		uint8_t stkp = 0x00; // Stack Pointer
		uint16_t pc = 0x0000; // Program Counter
		uint8_t status = 0x00; // Status Register

		void reset();
		void irq();
		void nmi();
		void clock();
		bool complete(); // Allow step by step execution

		// Link CPU to Bus
		void connectBus(Bus* n) { bus = n; }

		enum Flags
		{
			C = (1 << 0), // Carry Bit
			Z = (1 << 1), // Zero
			I = (1 << 2), // Disable Interrupts
			D = (1 << 3), // Decimal Mode
			B = (1 << 4), // Break
			U = (1 << 5), // Unused
			V = (1 << 6), // Overflow
			N = (1 << 7), // Negative
		};

	private:
		uint8_t GetFlag(Flags f);
		void SetFlag(Flags f, bool v);

		uint8_t read(uint16_t a);
		void write(uint16_t a, uint8_t d);

		uint8_t fetch();
		uint8_t fetched = 0x00;

		uint16_t addr_abs = 0x0000;
		uint16_t addr_rel = 0x00;
		uint8_t opcode = 0x00;
		uint8_t cycles = 0;

		uint32_t clock_count = 0;

		Bus* bus = nullptr;

		struct INSTRUCTION
		{
			std::string name;
			uint8_t(CPU::* operate)(void) = nullptr;
			uint8_t(CPU::* addrmode)(void) = nullptr;
			uint8_t     cycles = 0;
		};

		std::vector<INSTRUCTION> lookup;

	private:
		// Here comes the boilerplate :(
		// Addressing Modes

		// Implied Addressing Mode
		uint8_t IMP();
		// Immediate Addressing Mode
		uint8_t IMM();
		// Zero Page Addressing Mode
		uint8_t ZP0();	
		// Zero Page with X Offset Addressing Mode
		uint8_t ZPX();
		// Zero Page with Y Offset Addressing Mode
		uint8_t ZPY();
		// Absolute Addressing Mode
		uint8_t REL();
		// Absolute Addressing Mode
		uint8_t ABS();
		// Absolute with X Offset Addressing Mode
		uint8_t ABX();
		// Absolute with Y Offset Addressing Mode
		uint8_t ABY();	
		// Indirect Addressing Mode
		uint8_t IND();
		// Indirect X Addressing Mode
		uint8_t IZX();
		// Indirect Y Addressing Mode
		uint8_t IZY();

		// Normal Opcodes
		uint8_t ADC();	uint8_t AND();	uint8_t ASL();	uint8_t BCC(); uint8_t BCS();	uint8_t BEQ();	uint8_t BIT();	uint8_t BMI();
		uint8_t BNE();	uint8_t BPL();	uint8_t BRK();	uint8_t BVC(); uint8_t BVS();	uint8_t CLC();	uint8_t CLD();	uint8_t CLI();
		uint8_t CLV();	uint8_t CMP();	uint8_t CPX();	uint8_t CPY(); uint8_t DEC();	uint8_t DEX();	uint8_t DEY();	uint8_t EOR();
		uint8_t INC();	uint8_t INX();	uint8_t INY();	uint8_t JMP(); uint8_t JSR();	uint8_t LDA();	uint8_t LDX();	uint8_t LDY();
		uint8_t LSR();	uint8_t NOP();	uint8_t ORA();	uint8_t PHA(); uint8_t PHP();	uint8_t PLA();	uint8_t PLP();	uint8_t ROL();
		uint8_t ROR();	uint8_t RTI();	uint8_t RTS();	uint8_t SBC(); uint8_t SEC();	uint8_t SED();	uint8_t SEI();	uint8_t STA();
		uint8_t STX();	uint8_t STY();	uint8_t TAX();	uint8_t TAY(); uint8_t TSX();	uint8_t TXA();	uint8_t TXS();	uint8_t TYA();

		// Illegal Opcode (Placeholder)
		uint8_t IOP();

		// TODO: Implement illegal opcodes.
		/*
		// Illegal Opcodes
		uint8_t ASR();	uint8_t DCP();	uint8_t ISC();	uint8_t LAX();	uint8_t RLA();	uint8_t RRA();	uint8_t SAX();	uint8_t SLO();
		uint8_t SRE();	uint8_t SKB();	uint8_t SKW();	uint8_t ANC();	uint8_t ALR();	uint8_t ARR();	uint8_t AXS();  uint8_t AHX();
		uint8_t SHY();	uint8_t SHX();	uint8_t TAS();	uint8_t LAS();	uint8_t DCP();	uint8_t AXA();	uint8_t KIL();  uint8_t HLT();
		
		// UNSTABLE ILLEGAL OPCODE
		uint8_t XAA();
		*/

};
