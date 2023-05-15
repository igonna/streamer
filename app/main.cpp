#include <iostream>
#include <chrono>
#include <thread>
#include <csignal>
#include "streamer/streamer.hpp"
#include "logger/logger.hpp"

bool sig_close = false;
int exit_signal = 0;

void signal_handler(int signal) {
	std::cout << "signal: " << signal << std::endl;
	sig_close = true;
	exit_signal = signal;

	// restore default handler
	std::signal(signal, SIG_DFL);
}

int main()
{
	// register signals
	std::array signals = { SIGINT, SIGTERM, SIGQUIT, SIGTSTP, SIGKILL, SIGSEGV, SIGILL, SIGABRT };
	for (auto s : signals) {
		std::signal(s, signal_handler);
	}

	std::string app_name = "streamer";
	Logger logger{ app_name };

	std::string in_file_name = "/tmp/indata.txt";
	std::string out_file_name = "/tmp/outdata.txt";

	Streamer streamer = Streamer(in_file_name, out_file_name);

	// run update
	std::jthread t([&streamer]() {
		std::chrono::milliseconds update_pause{ 100 };
		while (!sig_close) {
			streamer.update();
			std::this_thread::sleep_for(update_pause);
		}
	});


	// run less (use shift+F for automatic update)
	std::string less_app = "less ";
	exit_signal = system((less_app + out_file_name).c_str());
	sig_close = true;

	logger.end_of_program(exit_signal);

	return 0;
}