#pragma once
#include <grpc/grpc.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

#include "ping.grpc.pb.h"

using grpc::Server;
using grpc::Status;
using grpc::ServerBuilder;
using grpc::ServerContext;

class ServerImpl final : public PingPong::Service {
public:
	Status SendPing(ServerContext* context, const Ping* request, Pong* reply) override;
};

void RunServer();
