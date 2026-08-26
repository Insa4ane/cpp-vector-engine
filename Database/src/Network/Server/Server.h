#include "../Socket.h"

class Server : public Socket {
private:
    int backlog;

public:
    Server(std::string IP, uint16_t port, int backlog);
    std::pair<std::string, bool> bind();
    std::pair<std::string, bool> listen();
    std::pair<std::string, int> accept(); 
};
