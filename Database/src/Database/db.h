#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <string>

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
    public:
        Database(std::string name);
        std::pair<std::string, bool>insert(const Record &record);
        std::pair<std::vector<std::string>, bool>split_string(std::string& desc);
        std::pair<Record, bool> vector_to_record(std::vector<std::string>&data);
        std::pair<std::string, bool>search(const Record& record);
};

