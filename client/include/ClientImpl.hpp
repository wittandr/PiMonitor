#pragma once
#include <grpcpp/grpcpp.h>
#include "ping.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

class ClientImpl {
public:
	ClientImpl(std::shared_ptr<Channel> channel) : stub_(PingPong::NewStub(channel)) {}
	std::string SendPing(const std::string& user);
private:
	std::unique_ptr<PingPong::Stub> stub_;
};
