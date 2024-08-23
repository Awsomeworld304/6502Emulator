#pragma once
#include <cstdint>
#include <array>

class RAM
{
private:
	//std::array<uint8_t, 64 * 1024>* ram;
	uint8_t *ram = new uint8_t[64 * 1024]; // 64KB of RAM

public:
	RAM();
	~RAM();
	uint8_t readRam(uint16_t addr, bool bReadOnly);
	void writeRam(uint16_t addr, uint8_t data);
	bool loadProgram(const char* path);
	void clearRam();
};