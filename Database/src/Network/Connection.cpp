#include <sys/socket.h>
#include "Connection.h"
#include <unistd.h>
#include <utility>
#include <arpa/inet.h>
/// @brief 
/// @param targetIP adres IP serwera 
/// @param targetPort  port sieciowy z ktorym chce sie polaczyc 
Connection::Connection(std::string targetIP, uint16_t targetPort): IP(targetIP), port(targetPort), descriptor(-1) {}



std::pair<std::string, bool> Connection:: create(){
    descriptor=socket(AF_INET, SOCK_STREAM, 0);
    if(descriptor==-1)
        return {"We cannot create the socket", false};
        
    return {"Success! The socket has been created", true};
}

std::pair<std::string, bool> Connection:: bind(){
    if(descriptor!=-1){
        return {"Error! The socket has not been created. (We have not descriptor to bind)", false};
    }
    ///
    sockaddr_in serverAdress;
    serverAdress.sin_family=AF_INET;
    serverAdress.sin_port=htons(port);

    if(inet_pton(AF_INET, IP.c_str(), &serverAdress.sin_addr)<=0)
    {
        return {"Error! We have a wrong IP", false};
    }
    if(::bind(descriptor, (struct sockaddr*)&serverAdress, sizeof(sockaddr_in)<0)){
        return {"Error! We cannot bind adrress",false};
    }

    return {"Success! The address has been binded", return true};
}


std::pair<std::string,bool> Connection::close(){
    if(descriptor!=-1){
        ::close(descriptor);
        descriptor=-1;
        return {"Success! The socket has been closed", true};
    }
    return {"Error! We cannot close the socket", false};
}