#include "01_class.h"
#include <zephyr/logging/log.h>
#include <iostream>

LOG_MODULE_REGISTER(class, LOG_LEVEL_INF);

namespace _01_class
{

void Log::SetLevel(LogLevel level)
{
	level_ = level;
}

void Log::Debug(const std::string &message)
{
	if (level_ <= LogLevel::kDebug) {
		std::cout << "[DEBUG] " << message << std::endl;
	}
}

void Log::Info(const std::string &message)
{
	if (level_ <= LogLevel::kInfo) {
		std::cout << "[INFO] " << message << std::endl;
	}
}

void Log::Warn(const std::string &message)
{
	if (level_ <= LogLevel::kWarning) {
		std::cout << "[WARNING] " << message << std::endl;
	}
}

void Log::Error(const std::string &message)
{
	if (level_ <= LogLevel::kError) {
		std::cout << "[ERROR] " << message << std::endl;
	}
}

int Entry()
{
	LOG_INF("Starting Class example...");

	Log log;
	log.SetLevel(Log::LogLevel::kInfo);
	log.Debug("This is a debug message");
	log.Info("This is an info message");
	log.Warn("This is a warning message");
	log.Error("This is an error message");
	std::cout << std::endl;
	return 0;
}

} // namespace _01_class
