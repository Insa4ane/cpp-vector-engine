#include <iostream>
#include "Server.h"
#include "../../Database/db.h"
#include <pybind11/embed.h>

namespace py=pybind11;

int main() {
    py::scoped_interpreter guard{};
    Server server("127.0.0.1", 8080, 5);
    server.create(); 
    server.bind();
    server.listen();
    std::cout << "Server is listening...." << std::endl;
    bool serverActive=true;
    Database db("Mojabazadanych");
    std::string serverResponse;
    auto [response, clientDesc] = server.accept(); 
    if (clientDesc >= 0) {
        std::cout << "Client is connected" << std::endl;
        while(serverActive){ /// 
            auto [msg, success] = server.receive(clientDesc);
           
            if (success) {
                std::stringstream ss(msg);
                std::string command;
                std::string pure_data;
                ss>>command>>pure_data;
                if (command == "STOP") {
                    serverActive = false;
                    serverResponse = "Success! Server is shutting down.";
                }
                std::pair<std::vector<std::string>, bool> written_data=db.split_data(pure_data);
                 if(written_data.second){
                     std::pair<Record, bool> record=db.vector_to_record(written_data.first);
                     if(record.second){
                        if(command=="ADD"){
                            std::pair<std::string, bool> results=db.insert(record.first);
                            serverResponse=results.first;
                        }
                        else if(command=="GET"){
                            std::pair<std::vector<Record>, bool> results=db.search(record.first);
                            if(results.second){
                                serverResponse="Success! Here is your reponse:\n";
                                for(const Record& result: results.first){
                                serverResponse += "- " + result.worker + " | " 
                                                    + result.language + " | " 
                                                    + std::to_string(result.exp) + " months\n";
                                }

                            }
                            else{
                                serverResponse="Error! Search failed or no results found.";
                            }
                        }
                     }
                     else{
                        serverResponse="Error! We cannot vector to record";
                     }
                 }
                 else{
                    serverResponse="Error! We cannot split data";
                 }

                
                server.send(serverResponse, clientDesc);
            }
        }
}
    
    server.close(); 
    return 0;
}