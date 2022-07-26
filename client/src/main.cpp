#include "ClientImpl.hpp"
int main(){
    std::string target_str = "localhost:50051";
    ClientImpl service(grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));
    while (true) {
        service.send_ping();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}