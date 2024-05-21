#include "ClientImpl.hpp"

#include "DataQuery.hpp"
#include <chrono>

void ClientImpl::send_ping() {
	PingRequest request;
	int id = rand();
	request.set_id(id);
	ClientContext context;
	PingResponse response;
	auto start = std::chrono::system_clock::now();
	Status status = stub_->Ping(&context, request, &response);
	auto end = std::chrono::system_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	if (status.ok() && response.id() == id)
		std::cout << "Latency: " << ms.count() << " ms\n";
	else {
		std::cout << status.error_code() << ": " << status.error_message() << std::endl;
	}
}

void DataImpl::send_data() {
	DataRequest request;
	std::string type = "cputemp";
	request.set_type(type);
	DataQuery::generate_log();
	DataQuery::process_log("openhardwaremonitor/log.txt");

	request.set_temp(DataQuery::data.cpu_temps[0]);
	ClientContext context;
	DataResponse response;
	Status status = stub_->DataTransfer(&context, request, &response);
	if (status.ok() && response.status() == "received")
		std::cout << type << " received" << std::endl;
	else {
		std::cout << status.error_code() << ": " << status.error_message() << std::endl;
	}

	ClientContext context2;
	DataResponse response2;
	type = "gputemp";
	request.set_type(type);
	float temp = DataQuery::data.gpu_temp;
	request.set_temp(temp);
	status = stub_->DataTransfer(&context2, request, &response2);
	if (status.ok() && response2.status() == "received")
		std::cout << type << " received" << std::endl;
	else {
		std::cout << status.error_code() << ": " << status.error_message() << std::endl;
	}
}
