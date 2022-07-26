#include "ClientImpl.hpp"

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
