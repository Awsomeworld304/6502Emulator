#pragma once
#include <cstdint>
#include <array>

#include "CPU.h"
#include "RAM.h"

class Bus
{
public:
	Bus();
	Bus(RAM*& ram);
	~Bus();
public:
	CPU cpu;
	RAM* ram;
	//std::array<uint8_t, 64 * 1024> ram;

public:
	void write(uint16_t addr, uint8_t data);
	uint8_t read(uint16_t addr, bool bReadOnly = false);
};
