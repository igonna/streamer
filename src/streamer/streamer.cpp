#include "streamer/streamer.hpp"
#include <iostream>
#include <fstream>

Streamer::Streamer(const std::filesystem::path& in_file_path, const std::filesystem::path& out_file_path) noexcept
	: in_file_path(in_file_path), out_file_path(out_file_path)
{
	std::ofstream out_file(out_file_path);
}

Streamer& Streamer::operator=(Streamer&& other) noexcept {
	in_file_path = std::move(other.in_file_path);
	out_file_path = std::move(other.out_file_path);
	return *this;
}

Streamer::~Streamer() {
	std::filesystem::remove(out_file_path);
}

void Streamer::update() {
	if (!std::filesystem::exists(in_file_path)) return;

	auto last_write_time = std::filesystem::last_write_time(in_file_path).time_since_epoch();
	if (last_write_time_old == last_write_time) return;

	std::ifstream in_file{ in_file_path, std::ios::binary };
	std::ofstream out_file{ out_file_path, std::ios::binary | std::ios::app };

	if (!in_file.is_open() || !out_file.is_open()) return;

	last_write_time_old = last_write_time;

	in_file.seekg(overal_bytes_read, std::ios::beg);

	// read and out
	char ch;
	size_t byte_count = 0;
	while (in_file.get(ch)) {
		++byte_count;
		out_file.put(ch);
	}
	overal_bytes_read += byte_count;
}