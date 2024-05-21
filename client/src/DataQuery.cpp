#include "DataQuery.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>


void DataQuery::generate_log(){
	std::string cmd = std::filesystem::current_path().string()
		+ "/openhardwaremonitor/OpenHardwareMonitorReport.exe > openhardwaremonitor/log.txt";
	std::system(cmd.c_str());
}

void DataQuery::process_log(const std::string& path) {
	std::ifstream log;
	log.open(path);
	std::string line;
	DataQuery::data.cpu_temps.clear();
	bool all_cores = false;
	DataQuery::log_mutex.lock();

	// Get core temps and number of cores
	while (std::getline(log, line) && !all_cores) {
		std::smatch s;
		std::regex_match(line, s, DataQuery::re_cputemp);
		if (s.size() == 0)
			continue;
		else {
			DataQuery::data.cpu_temps.push_back(stoi(s[2].str()));
			int n_cpu = stoi(s[1].str());
			DataQuery::data.n_cores = n_cpu > DataQuery::data.n_cores ? n_cpu : DataQuery::data.n_cores;
			while (std::getline(log, line)) {
				std::regex_match(line, s, DataQuery::re_cputemp);
				if (s.size() == 0) {
					all_cores = true;
					break;
				}
				DataQuery::data.cpu_temps.push_back(stoi(s[2].str()));
				int n_cpu = stoi(s[1].str());
				DataQuery::data.n_cores = n_cpu > DataQuery::data.n_cores ? n_cpu : DataQuery::data.n_cores;
			}

		}
	}

	// Get used ram
	while (std::getline(log, line)) {
		std::smatch s;
		std::regex_match(line, s, DataQuery::re_used_ram);
		if (s.size() == 0)
			continue;
		DataQuery::data.used_ram = stof(s[1].str());
		break;
	}

	// Get free ram
	while (std::getline(log, line)) {
		std::smatch s;
		std::regex_match(line, s, DataQuery::re_free_ram);
		if (s.size() == 0)
			continue;
		DataQuery::data.free_ram = stof(s[1].str());
		break;
	}

	// Get gpu temp
	while (std::getline(log, line)) {
		std::smatch s;
		std::regex_match(line, s, DataQuery::re_gputemp);
		if (s.size() == 0)
			continue;
		DataQuery::data.gpu_temp = stof(s[1].str());
		break;
	}

	// Get free dram
	while (std::getline(log, line)) {
		std::smatch s;
		std::regex_match(line, s, DataQuery::re_free_dram);
		if (s.size() == 0)
			continue;
		DataQuery::data.free_dram = stof(s[1].str());
		break;
	}

	// Get used dram
	while (std::getline(log, line)) {
		std::smatch s;
		std::regex_match(line, s, DataQuery::re_used_dram);
		if (s.size() == 0)
			continue;
		DataQuery::data.used_dram = stof(s[1].str());
		break;
	}

	DataQuery::log_mutex.unlock();

}

