#include "db.h"

namespace py=pybind11;

Database::Database(std::string name) : name(name), recordID(0) {
    try{
        py::module_ sys = py::module_::import("sys"); 
        sys.attr("path").attr("append")("./Model/src/agent");
        py::module_ agent_module = py::module_::import("agent");

        py::object agent_class = agent_module.attr("VectorAgent");
        ai_agent = agent_class();
    }
    catch(const py::error_already_set& e){
        std::cerr <<"Error! We cannot connect with agent because: "<< e.what() << '\n';

    }
}

std::pair<std::string, bool> Database::insert(const Record& record) {
    Record copy_record = record;
    copy_record.id=recordID;

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

std::pair<std::vector<std::string>, bool> Database::split_data(std::string& desc){
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


std::pair<std::vector<Record>, bool> Database::search(const Record& record){ 
    if(data.empty()){
        return {{},false};
    }
    std::vector<Record> results;
    for(const auto& [id, rec]:data){
        if(rec.language==record.language){
            results.push_back(rec);
        }
    }
        if(results.size()==0){
            try{
                std::string text_to_ai=record.language+" "+std::to_string(record.exp);
                std::vector<float> query_vector=ai_agent.attr("text_to_vector")(text_to_ai).cast<std::vector<float>>();
                ///nastepnie potrzebne bedzie napisac logike tych wektorow
                std::vector<std::pair<double,Record>> distances;
                for(const auto& [id, rec]:data){
                    std::pair<double, bool> distance=cosine_similarity(query_vector, rec.vector);
                    if(distance.second){
                        distances.push_back({distance.first, rec}); 
                    }
                }
                if (distances.size()==0) return {{}, false};

                std::sort(distances.begin(), distances.end(), [](const auto&a, const auto&b){return a.first>b.first; }); ///sorted data
                size_t limit = std::min(Database::EXPECTED_RESULT, distances.size());
                for(size_t i = 0; i < limit; ++i){
                    results.push_back(distances[i].second);
                }
            }
            catch(const std::exception& e){
                
                return{{}, false};
            }

        }

        return{results, true};
}

///similarity of vectors , looking vector, and record that is in database
std::pair<double, bool> Database::cosine_similarity(const std::vector<float>& looking_record, const std::vector<float>& data_record){
    if(looking_record.size() != data_record.size() || looking_record.empty()){
    return {0.0, false};
    }

    double dot_product = 0.0;
    double norm_a = 0.0;
    double norm_b = 0.0;
    
    for (size_t i = 0; i < looking_record.size(); ++i) {
        dot_product += looking_record[i] * data_record[i];
        norm_a += looking_record[i] * looking_record[i];
        norm_b += data_record[i] * data_record[i];
    }

    if (norm_a <= 0.0 || norm_b <=0.0) return {0.0, false};
    
    return {dot_product / (std::sqrt(norm_a) * std::sqrt(norm_b)), true};

}

