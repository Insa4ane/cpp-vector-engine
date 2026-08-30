#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <string>
#include <pybind11/embed.h>
#include <pybind11/stl.h>
#include <cmath>
#include <algorithm>


struct Record{
    int id;
    std::string worker;
    std::string language;
    int exp; ///in months 
    static constexpr size_t EXPECTED_FIELDS = 3;
    std::vector<float> vector; ///for agent
};

class Database{
    private:
        std::string name;
        std::unordered_map<int, Record> data;
        int recordID=0; 
        py::object ai_agent;
        static constexpr size_t EXPECTED_RESULT=3; 
    public:
        Database(std::string name);
        std::pair<std::string, bool>insert(const Record &record);
        std::pair<std::vector<std::string>, bool>split_data(std::string& desc);
        std::pair<Record, bool> vector_to_record(std::vector<std::string>&data);
        std::pair<std::vector<Record>, bool>search(const Record& record);
        std::pair<double, bool> cosine_similarity(const std::vector<float>& a, const std::vector<float>& b);
};

