#include "ClientImpl.hpp"

int main(){
    std::string target_str = "localhost:50051";
    ClientImpl service(grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));
    std::string user("world");
    std::string reply = service.SendPing(user);
    std::cout << "Received: " << reply << std::endl;
}