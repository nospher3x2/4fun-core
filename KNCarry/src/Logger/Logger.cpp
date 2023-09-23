#include "Logger.hpp"
#include <cstdarg>
#include <Windows.h>
#include "../Drawing/Console/Console.hpp"
#include <shlobj_core.h>

std::shared_ptr<std::fstream>      Logger::FileStream = nullptr;
std::mutex                         Logger::LoggerMutex;
std::deque<std::string>            Logger::BufferDebug;

void Logger::Initialize()
{
	char path[1024];
	if (!SHGetSpecialFolderPathA(nullptr, path, CSIDL_APPDATA, TRUE))
		throw std::exception("Fatal error. Couldn't get appdata folder.");

	auto pathFileLogger = std::string(path) + "\\" + "TwoHundred";
	pathFileLogger.append("\\");
	pathFileLogger.append("logs.txt");
	FileStream = std::make_shared<std::fstream>(pathFileLogger.c_str(), std::ios::out | std::ios::trunc);
}

void Logger::Info(const char* str, ...)
{
	va_list va;
	va_start(va, str);
	WriteMessage(ImVec4(1.f, 1.f, 1.f, 1.f), false, str, va);
	va_end(va);
}

void Logger::Warn(const char* str, ...)
{
	va_list va;
	va_start(va, str);
	WriteMessage(ImVec4(1.f, 1.f, 0.f, 1.f), false, str, va);
	va_end(va);
}

void Logger::Error(const char* str, ...)
{
	va_list va;
	va_start(va, str);
	WriteMessage(ImVec4(1.f, 0.f, 0.f, 1.f), true, str, va);
	va_end(va);
}

void Logger::PushDebug(const char* str, ...)
{
	LoggerMutex.lock();
	char msg[4000];
	va_list va;
	va_start(va, str);
	vsprintf_s(msg, str, va);
	va_end(va);

	BufferDebug.emplace_back(msg);
	LoggerMutex.unlock();
}

void Logger::DumpDebug()
{
	LoggerMutex.lock();
	for (const auto& msg : BufferDebug) {
		FileStream->write("[debug] ", 8);
		FileStream->write(msg.c_str(), msg.size());
		FileStream->write("\n", 1);
	}
	LoggerMutex.unlock();
}

void Logger::ClearDebug()
{
	LoggerMutex.lock();
	BufferDebug.clear();
	LoggerMutex.unlock();
}

void Logger::WriteMessage(const ImVec4& colorConsole, const bool forceFlush, const char* formatStr, const va_list formatArgs)
{
	static uintptr_t lastFlushTick = 0;

	LoggerMutex.lock();

	char msg[4000];
	vsprintf_s(msg, formatStr, formatArgs);

	*FileStream << msg << "\n";

	const auto line = new ConsoleStringLine();
	line->text = msg;
	line->color = colorConsole;
	Console::AddLine(line);

	if (forceFlush || GetTickCount64() > lastFlushTick) {
		FileStream->flush();
		lastFlushTick = GetTickCount64() + 100;
	}

	LoggerMutex.unlock();
}