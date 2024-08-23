#include "RAM.h"
#include "../Utils/BetterConsole.h"

RAM::RAM()
{
	// Zero out RAM
	for (int i = 0; i < 64 * 1024; i++)
		ram[i] = 0;
}

RAM::~RAM()
{
	delete [] ram;
}

uint8_t RAM::readRam(uint16_t addr, bool bReadOnly)
{
	if (addr >= 0x0000 && addr <= 0xFFFF)
		return ram[addr];
	return 0x00;
}

void RAM::writeRam(uint16_t addr, uint8_t data)
{
	if (addr >= 0x0000 && addr <= 0xFFFF)
		//ram[addr] = data;
		ram[addr] = data;	
}

/**
 * Load a program into RAM.
 * @param path Path to the program.
 * @return True if the program was loaded successfully, false otherwise.
*/
bool RAM::loadProgram(const char* path)
{
#pragma warning(suppress : 4996)
	FILE* file = fopen(path, "rb");
	if (file == nullptr)
	{
		BetterConsole::Error("[RAM] Error loading program: " + std::string(path));
		return false;
	}
	// load file contents into RAM
	fread(ram, 1, 64 * 1024, file);
	fclose(file);
	return true;
}

void RAM::clearRam()
{
	for (int i = 0; i < 64 * 1024; i++)
		ram[i] = 0;
}
