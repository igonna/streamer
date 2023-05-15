#pragma once

#include <string>

class Logger {
public:
	Logger() = delete;
	explicit Logger(const std::string& app_name) noexcept;
	virtual ~Logger();
	
	void warning(const std::string& message) const noexcept;
	void info(const std::string& message) const noexcept;
	void error(const std::string& message) const noexcept;
	void end_of_program(int signal) const noexcept;
private:
	std::string app_name;
};