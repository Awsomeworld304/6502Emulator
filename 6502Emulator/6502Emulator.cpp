#include <iostream>
#include <string>

#include "Utils/BetterConsole.h"

#include "Core/CPU.h"
#include "Core/Bus.h"
#include "Core/RAM.h"

int main()
{
    BetterConsole console;
    console.SetTitle("6502 Emulator");

    RAM* ram = new RAM();
    CPU cpu;
    Bus* bus = new Bus(ram);

    console.Log("CPU Reset in progress.");
    cpu.reset();
    console.Success("CPU Reset complete.");

    getchar();

    delete bus;
    delete ram;
    return 0;
}
