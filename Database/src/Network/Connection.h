#include <iostream>
#include <cstdint>
#include <utility>



class Connection{
    private:
        std::string IP;
        uint16_t port;
        int descriptor;
    public:
    Connection(std::string IP, uint16_t);
    std::pair<std::string, bool> create();
    std::string listen();
    std::pair<std::string, bool> close();
    std::pair<std::string, bool> accept();
    bool send(const std::string& message, int clientDescriptr);
    bool connect();
    bool bind();

};