#include "db.h"

Database::Database(std::string name) : name(name), recordID(recordID) {}

std::pair<std::string, bool> Database::insert(const Record& record) {
    data[recordID] = record;
    recordID++;
    return {"Success! The record has been added to database named: "+name, true};
}

std::pair<std::vector<std::string>, bool> split_data(std::string& desc){
    std::vector<std::string> results; ///vector for ready data
    std::string result;
    std::stringstream stream(desc);

    while(std::getline(stream, result, ',')){
        results.push_back(result);
    }
    if(results.size()>Record::EXPECTED_FIELDS){
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


std::pair<std::string, bool> Database::search(const Record& record){ 

}

