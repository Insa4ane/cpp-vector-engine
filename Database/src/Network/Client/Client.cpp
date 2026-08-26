#include "Client.h"
#include <sys/socket.h>
#include <arpa/inet.h>


Client::Client(std::string IP, uint16_t port) : Socket(IP, port) {}

std::pair<std::string, bool> Client::connect() {
    if (descriptor == -1) {
        return {"Error! The socket has not been created (no descriptor).", false};
    }
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port); 
    if (inet_pton(AF_INET, IP.c_str(), &serverAddress.sin_addr) <= 0) {
        return {"Error! Invalid IP address format.", false};
    }
    if (::connect(descriptor, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        return {"Error! Connection failed. Is the server running and listening?", false};
    }
    return {"Success! Connected to the server.", true};
}