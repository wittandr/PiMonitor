#include "ServerImpl.hpp"


Status ServerImpl::SendPing(ServerContext* context, const Ping* request, Pong* reply){
	std::cout << "Request from: " << request->message() << std::endl;
	std::string prefix("Hello ");
	reply->set_message(prefix + request->GetTypeName());
	return Status::OK;
}

void RunServer() {
	std::string server_address("0.0.0.0:50051");
	ServerImpl service;
	grpc::EnableDefaultHealthCheckService(true);
	ServerBuilder builder;
	builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
	builder.RegisterService(&service);
	std::unique_ptr<Server> server(builder.BuildAndStart());
	std::cout << "Server listening on " << server_address << std::endl;
	server->Wait();
}
