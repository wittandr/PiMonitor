#include "ClientImpl.hpp"
int main(){
    //std::string target_str = "192.168.0.6:50051";
    std::string target_str = "127.0.0.1:50051";
    ClientImpl service(grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));
    DataImpl dataservice(grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));
    while (true) {
        service.send_ping();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        dataservice.send_data();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}