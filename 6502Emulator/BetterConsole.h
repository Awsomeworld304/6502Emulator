#pragma once

#include <string>
#include <iostream>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define PURPLE  "\033[35m"
#define WHITE   "\033[37m"

class BetterConsole
{

public:
	BetterConsole();
	~BetterConsole();

	static void Log(const std::string& message);
	static void Warning(const std::string& message);
	static void Error(const std::string& message);
	static void FatalError(const std::string& message);
	static void FatalError(const std::string& message, const bool exit);
	static void Success(const std::string& message);

public:
	void Box(const std::string& message, const std::string& color);

public:
	void SetTitle(const std::string& title);

public:
	static BetterConsole& getInstance()
	{
		static BetterConsole instance;
		return instance;
	}

private:
	BetterConsole(BetterConsole const&) = delete;
	void operator=(BetterConsole const&) = delete;
};