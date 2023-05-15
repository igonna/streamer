#include "logger/logger.hpp"

#include <syslog.h>
#include <cstring>
#include <csignal>

Logger::Logger(const std::string& app_name) noexcept : app_name(app_name) {
	openlog(app_name.c_str(), LOG_PID | LOG_NDELAY, LOG_USER);
	info(std::string("(") + app_name + ") started.");
}

Logger::~Logger()
{
	closelog();
}

void Logger::warning(const std::string& message) const noexcept
{
	syslog(LOG_INFO, "%s", message.c_str());
}

void Logger::info(const std::string& message) const noexcept
{
	syslog(LOG_WARNING, "%s", message.c_str());
}

void Logger::error(const std::string& message) const noexcept
{
	syslog(LOG_ERR, "%s", message.c_str());
}

void Logger::end_of_program(int signal) const noexcept
{
	std::string final_speech = "(" + app_name + ") closed with signal: " + strsignal(signal);
	info(final_speech);
}


