#pragma once

#include <filesystem>

class Streamer {
public:
	Streamer() = default;
	explicit Streamer(const std::filesystem::path& in_file_path, const std::filesystem::path& out_file_path) noexcept;
	Streamer& operator=(Streamer&& other) noexcept;
	virtual ~Streamer();
	void update();

private:
	std::filesystem::path in_file_path;
	std::filesystem::path out_file_path;

	size_t overal_bytes_read = 0;
	std::chrono::nanoseconds last_write_time_old;
};