#include <sys/socket.h>
#include "Server.h"
#include <unistd.h>
#include <utility>
#include <arpa/inet.h>
/// @brief 
/// @param targetIP adres IP serwera 
/// @param targetPort  port sieciowy z ktorym chce sie polaczyc 
Server::Server(std::string IP, uint16_t port, int backlog) : Socket(IP, port), backlog(backlog) {};

std::pair<std::string, bool> Server:: bind(){
    if(descriptor==-1){
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
    if(::bind(descriptor, (struct sockaddr*)&serverAdress, sizeof(sockaddr_in))<0){
        return {"Error! We cannot bind adrress",false};
    }

    return {"Success! The address has been binded",true};
}


std::pair<std::string, bool> Server::listen(){
    if(descriptor==-1){

        return {"Error! The socket has not created, so listen is impossible", false};
    }
    if(::listen(descriptor, backlog)<0){
        return{"Error! We cannot start listening on this socket", false};
    }
    ///if everything is ok we return...
    return{"Success! The server is now listening for incoming connection", true};
    
}

std::pair<std::string, int> Server::accept(){
    if(descriptor==-1){
        return {"Error! The socket has not created, so accept incoming connection is impossible", 0};
    }
    sockaddr_in sockClient;
    socklen_t clientSize=sizeof(sockClient);

    int clientDescriptor=::accept(descriptor, (struct sockaddr*)&sockClient, &clientSize);
    if(clientDescriptor<0){
        return{"Error! We cannot create the socket for client", 0};
    }
    return{"Success! The socket for client has been created", clientDescriptor};
}


