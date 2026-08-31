#include <iostream>
#include "Client.h"
#include <string>

int main() {
    Client client("127.0.0.1", 8080); 
    
    client.create(); 
    auto [msg, success] = client.connect(); 
    
    if (success) {
        std::cout << "Connected with server!" << std::endl;
        std::string message;
        while(true){
        std::getline(std::cin, message); 
        if (!message.empty()) client.send(message, client.getDescriptor());
        auto [reply, recvSuccess] = client.receive(client.getDescriptor());
        if (recvSuccess) {
            std::cout << "Server response: " << reply << std::endl;
        }
        if (message == "STOP") {
                std::cout << "Disconnect a client" << std::endl;
                break; 
            }
    }
    } else {
        std::cout << "Connection failed: " << msg << std::endl;
    }
    
    client.close();
    return 0;
}