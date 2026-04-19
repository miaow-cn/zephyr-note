#include <zephyr/logging/log.h>
#include <iostream>
#include <01_class.hpp>

LOG_MODULE_REGISTER(class, LOG_LEVEL_INF);

void Log::set_level(LogLevel level)
{
    m_level = level;
}

void Log::debug(const std::string& message)
{
    if (m_level <= LogLevel::Debug) {
        std::cout << "[DEBUG] " << message << std::endl;
    }
}

void Log::info(const std::string& message)
{
    if (m_level <= LogLevel::Info) {
        std::cout << "[INFO] " << message << std::endl;
    }
}

void Log::warn(const std::string& message)
{
    if (m_level <= LogLevel::Warning) {
        std::cout << "[WARNING] " << message << std::endl;
    }
}

void Log::error(const std::string& message)
{
    if (m_level <= LogLevel::Error) {
        std::cout << "[ERROR] " << message << std::endl;
    }
}

int class_entry()
{
    LOG_INF("Starting Class example...");

    Log log;
    log.set_level(Log::LogLevel::Info);
    log.debug("This is a debug message");
    log.info("This is an info message");
    log.warn("This is a warning message");
    log.error("This is an error message");
    return 0;
}