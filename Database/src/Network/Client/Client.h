#include <iostream>
#include <utility>
#include "../Socket.h"

class Client : public Socket{
    public:
        Client(std::string IP, uint16_t port);
        std::pair<std::string, bool> connect();

};