#include "ClientImpl.hpp"

std::string ClientImpl::SendPing(const std::string& user) {
	Ping request;
	request.set_message(user);
	Pong reply;
	ClientContext context;
	Status status = stub_->SendPing(&context, request, &reply);
	if (status.ok())
		return reply.message();
	else {
		std::cout << status.error_code() << ": " << status.error_message() << std::endl;
		return "RPC failed";
	}
}
