#include "pch.h"
#include "Log.h"

Log::Color Log::currentColor = 0;

void Log::LogType(const std::string& logType, const Color& color)
{
	if (currentColor != color)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
		currentColor = color;
	}
	std::cout << logType << ' ';
}
