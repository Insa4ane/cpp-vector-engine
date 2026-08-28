#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <string>
#include <pybind11/embed.h>
#include <pybind11/stl.h>

struct Record{
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
    public:
        Database(std::string name);
        std::pair<std::string, bool>insert(const Record &record);
        std::pair<std::vector<std::string>, bool>split_string(std::string& desc);
        std::pair<Record, bool> vector_to_record(std::vector<std::string>&data);
        std::pair<std::vector<std::pair<int, Record>>, bool>search(const Record& record);
};

