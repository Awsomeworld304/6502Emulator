#include <iostream>
#include "Bus.h"
#include "../Utils/BetterConsole.h"

Bus::Bus(RAM*& ram)
{
	cpu.connectBus(this);
	this->ram = ram;
	//ram.fill(0);
}

Bus::~Bus()
{
	// Literally do nothing dumbass.
}

void Bus::write(uint16_t addr, uint8_t data) 
{
	if (addr >= 0x0000 && addr <= 0xFFFF)
		try {
			ram->writeRam(addr, data);
			//ram[addr] = data;
		}
		catch (uint16_t e) {
			BetterConsole::Error("[BUS] Error writing to RAM at address: " + addr);
		}
}

uint8_t Bus::read(uint16_t addr, bool bReadOnly)
{
	try {
		return ram->readRam(addr, bReadOnly);
		//return ram[addr];
	}
	catch (uint16_t e) {
		BetterConsole::Error("[BUS] Error reading RAM at address: " + addr);
	}
	return 0x00;
}