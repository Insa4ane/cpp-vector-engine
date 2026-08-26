#include <iostream>
#include "Client.h"

int main() {
    Client client("127.0.0.1", 8080); 
    
    client.create(); 
    auto [msg, success] = client.connect(); 
    
    if (success) {
        std::cout << "Connected with server!" << std::endl;
        
        client.send("Hi! Here is your first client", client.getDescriptor());
        
        auto [reply, recvSuccess] = client.receive(client.getDescriptor());
        if (recvSuccess) {
            std::cout << "Server response: " << reply << std::endl;
        }
    } else {
        std::cout << "Connection failed: " << msg << std::endl;
    }
    
    client.close();
    return 0;
}