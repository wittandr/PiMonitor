#pragma once
#include <vector>
#include <mutex>
#include <regex>

constexpr std::string_view cputemp_regex = "^.+CPU Core #(\\d+)\\s+:\\s+\\d+\\s+\\d+\\s+(\\d+).+temperature.+$";
constexpr std::string_view used_ram_regex = "^.+Used Memory\\s+:\\s+(\\d+\\.\\d+).+ram.+$";
constexpr std::string_view free_ram_regex = "^.+Available Memory\\s+:\\s+(\\d+\\.\\d+).+ram.+$";
constexpr std::string_view gputemp_regex = "^.+GPU Core\\s+:\\s+(\\d+).+temperature.+$";
constexpr std::string_view used_dram_regex = "^.+GPU Memory Used\\s+:\\s+(\\d+\\.\\d+).+$";
constexpr std::string_view free_dram_regex = "^.+GPU Memory Free\\s+:\\s+(\\d+\\.\\d+).+$";

struct HardwareData {
	int n_cores = 1;
	std::vector<int> cpu_temps;
	float used_ram;
	float free_ram;
	int gpu_temp;
	float used_dram;
	float free_dram;
};

class DataQuery {
public:
	static void process_log(const std::string& path);
	static void generate_log();
	inline static HardwareData data = HardwareData();
	inline static std::mutex log_mutex = std::mutex();
	inline const static std::regex re_cputemp = std::regex(std::string(cputemp_regex));
	inline const static std::regex re_used_ram = std::regex(std::string(used_ram_regex));
	inline const static std::regex re_free_ram = std::regex(std::string(free_ram_regex));
	inline const static std::regex re_gputemp = std::regex(std::string(gputemp_regex));
	inline const static std::regex re_used_dram = std::regex(std::string(used_dram_regex));
	inline const static std::regex re_free_dram = std::regex(std::string(free_dram_regex));
};