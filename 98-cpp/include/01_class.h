#ifndef CLASS_HPP
#define CLASS_HPP

#include <string>

namespace _01_class
{
class Log
{
public:
	enum class LogLevel {
		kDebug,
		kInfo,
		kWarning,
		kError
	};

	void SetLevel(LogLevel level);

	void Debug(const std::string& message);
	void Info(const std::string& message);
	void Warn(const std::string& message);
	void Error(const std::string& message);

private:
	LogLevel level_ = LogLevel::kInfo;
};

int Entry(void);

}

#endif /* CLASS_HPP */
