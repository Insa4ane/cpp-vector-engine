#include"Socket.h"
#include<sys/socket.h>
#include <unistd.h>

Socket::Socket(std::string targetIP, uint16_t targetPort): IP(targetIP), port(targetPort) {}


std::pair<std::string, bool> Socket::create(){
    descriptor=socket(AF_INET, SOCK_STREAM, 0);
    if(descriptor==-1)
        return {"We cannot create the socket", false};
        
    return {"Success! The socket has been created", true};
}

std::pair<std::string,bool> Socket::close(){
    if(descriptor!=-1){
        ::close(descriptor);
        descriptor=-1;
        return {"Success! The socket has been closed", true};
    }
    return {"Error! We cannot close the socket", false};
}
