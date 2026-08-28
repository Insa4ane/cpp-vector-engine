#include "db.h"

namespace py=pybind11;

Database::Database(std::string name) : name(name), recordID(0) {
    try{
        py::module_ sys = py::module_::import("sys"); 
        sys.attr("path").attr("append")("./Model/src/agent");
        py::module_ agent_module = py::module_::import("agent");

        py::object agent_class = agent_module.attr("VectorAgent");
        ai_agent = agent_class();
        std::cout<<"Success! The agent has been connected!";
    }
    catch(const py::error_already_set& e){
        std::cerr <<"Error! We cannot connect with agent because: "<< e.what() << '\n';

    }
}

std::pair<std::string, bool> Database::insert(const Record& record) {
    Record copy_record = record;

    try {
        std::string text_for_ai = copy_record.language + " " + std::to_string(copy_record.exp);
        std::vector<float> embedding = ai_agent.attr("text_to_vector")(text_for_ai).cast<std::vector<float>>();

        copy_record.vector = embedding; 

    } catch (const py::error_already_set& e) {
        return {"Error! Problem with insert data(vector)" + std::string(e.what()), false};
    }

    data[recordID] = copy_record;
    recordID++;
    
    return {"Success! The record has been added to database named: " + name, true};
}

std::pair<std::vector<std::string>, bool> split_data(std::string& desc){
    std::vector<std::string> results; ///vector for ready data
    std::string result;
    std::stringstream stream(desc);

    while(std::getline(stream, result, ',')){
        results.push_back(result);
    }
    if(results.size()!=Record::EXPECTED_FIELDS){
        return {{"Error!,Its,Imposible,to,split,data"}, false};
    }

    return{results, true};
}

std::pair<Record, bool> Database::vector_to_record(std::vector<std::string>&data){
    Record record;
    try{
        record.worker=data[0];
        record.language=data[1];
        record.exp=std::stoi(data[2]);
    }
    catch(const std::exception& e){
        return {record, false};
    }
    return {record, true};
}


std::pair<std::vector<std::pair<int, Record>>, bool> Database::search(const Record& record){ 
    if(data.empty()){
        return {{},false};
    }
    std::vector<std::pair<int, Record>> results;
    for(const auto& [id, rec]:data){
        if(rec.language==record.language){
            std::pair<int, Record> result;
            result={id, rec};
            results.push_back(result);
        }
    }
        if(results.size()==0){
            ///w tym miejscu bedzie logika naszego agenta ktory bedzie odczytywal wektory i zwracal vectory
        }

        return{results, true}; ///here is every
}

