#include "BetterConsole.h"
#include <iostream>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#define DIV 1048576 
#define WIDTH 7
#endif

using namespace std;

void BetterConsole::Log(const string& message)
{
	cout << BLUE << message << RESET << endl;
}

void BetterConsole::Log(const int message)
{
	cout << BLUE << message << RESET << endl;
}

void BetterConsole::Warning(const std::string& message)
{
	cout << YELLOW << message << RESET << endl;
}

void BetterConsole::Error(const std::string& message)
{
	cout << RED << message << RESET << endl;
}

void BetterConsole::FatalError(const std::string& message)
{
	cout << PURPLE << message << RESET << endl;
	std::exit(1);
}

void BetterConsole::FatalError(const std::string& message, const bool exit)
{
	cout << PURPLE << message << RESET << endl;
	if (exit)
	{
		std::exit(1);
	}
}

void BetterConsole::Success(const std::string& message)
{
	cout << GREEN << message << RESET << endl;
}

// Make a 4:3 box with a message in the middle and with a color
void BetterConsole::Box(const std::string& message, const std::string& color)
{
int messageLength = message.length();
	int boxWidth = messageLength + 4;
	int boxHeight = 3;

	// Top
	std::cout << color << "+";
	for (int i = 0; i < boxWidth; i++)
	{
		std::cout << "-";
	}
	std::cout << "+" << RESET << endl;

	// Middle
	std::cout << color << "|  " << RESET << message << color << "  |" << RESET << endl;

	// Bottom
	std::cout << color << "+";
	for (int i = 0; i < boxWidth; i++)
	{
		cout << "-";
	}
	cout << "+" << RESET << endl;
}

void BetterConsole::SetTitle(const std::string& title)
{
	// We love Windows!! (not)
	#ifdef _WIN32
	SetConsoleTitleA(title.c_str());
	#else
	cout << "\033]0;" << title << "\007";
	#endif
}

BetterConsole::BetterConsole()
{
	Success("BetterConsole initialized!");
}

BetterConsole::~BetterConsole()
{
}
