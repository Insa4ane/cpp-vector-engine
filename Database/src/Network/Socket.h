#include <iostream>
#include <cstdint>
#include <utility>


class Socket{
    protected:
        std::string IP;
        uint16_t port;
        int descriptor=-1;
    public:
        Socket(std::string IP, uint16_t port);
        std::pair<std::string, bool> create();
        std::pair<std::string, bool> close();
        std::pair<std::string, bool> receive(); 
        bool send(const std::string& message, int clientDescriptor);
        virtual ~Socket();


};