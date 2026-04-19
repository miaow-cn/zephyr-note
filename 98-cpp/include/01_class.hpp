#ifndef CLASS_HPP
#define CLASS_HPP

#include <string>

class Log
{
public:
	enum class LogLevel {
		Debug,
		Info,
		Warning,
		Error
	};

	void set_level(LogLevel level);

	void debug(const std::string& message);
	void info(const std::string& message);
	void warn(const std::string& message);
	void error(const std::string& message);

private:
	LogLevel m_level = LogLevel::Info;
};

int class_entry(void);

#endif /* CLASS_HPP */
