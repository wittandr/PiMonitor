#pragma once
#include <grpcpp/grpcpp.h>
#include "ping.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

class ClientImpl {
public:
	ClientImpl(std::shared_ptr<Channel> channel) : stub_(PingService::NewStub(channel)) {}
	void send_ping();
private:
	std::unique_ptr<PingService::Stub> stub_;
};
