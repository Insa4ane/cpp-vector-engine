#include <iostream>
#include "Server.h"

int main() {
    Server server("127.0.0.1", 8080, 5);
    
    server.create(); 
    server.bind();
    server.listen();
    std::cout << "Server is listening...." << std::endl;

    
    auto [response, clientDesc] = server.accept(); 
    if (clientDesc >= 0) {
        std::cout << "Client is connected" << std::endl;
        
        
        auto [msg, success] = server.receive(clientDesc);
        if (success) {
            std::cout << "Client write" << msg << std::endl;
            
            server.send("I get your message! Seeya", clientDesc);
        }
    }
    
    server.close(); 
    return 0;
}