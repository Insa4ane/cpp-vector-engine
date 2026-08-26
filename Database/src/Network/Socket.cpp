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

std::pair<std::string, bool> Socket::send(const std::string& message, int clientDescriptor){
    if(clientDescriptor<0){
        return {"Error! We cannot send data, The socket does not exist", false};
    }

    ssize_t bytesSent=::send(clientDescriptor, message.c_str(), message.size(), 0);
    if(bytesSent<0){
        return{"Error! We cannot sent data", false};
    }

    return {"Success! Data have been already sent", true};


}

std::pair<std::string, bool> Socket::receive(int clientSocket){
    if (clientSocket<0){
        return {"Error! We cannor receive data from the client", false};
    }
    char buffer[4096];
    
    ssize_t bytesReceive=::recv(clientSocket, buffer, sizeof(buffer)-1, 0);

    if(bytesReceive<0){
        return {"Error! We have a probem with receive data", false};
    }
    else if(bytesReceive==0){
        return {"The other side close a connect", false};
    }
    return{"Success! We receive a data: "+std::string(buffer), true};
}

int Socket::getDescriptor(){
    return descriptor;
}

Socket::~Socket() {}