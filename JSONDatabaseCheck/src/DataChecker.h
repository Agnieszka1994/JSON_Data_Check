#pragma once
#include "TimetableUnit.h"
#include <set>
namespace datachecker
{
    class DataChecker
    {
    public:
        DataChecker() = default;
        DataChecker(DataChecker&) = delete;
        DataChecker(DataChecker&&) = delete;
        DataChecker(std::string&);
        
        void uploadData(std::string data);
        void printErrors();

    private:
      
        
        void buildMapOfLines();
        void checkDataTypes(std::string& data);
        
        enum Error { BusId, StopId, StopName, NextStop, StopType, Time };
        void insertError(int objId, Error e);
        
        int sumOfErrorValues(const std::pair<int, std::vector<Error>>& obj, Error errorValue);
        std::unordered_map<int, std::vector<Error>> errors{};
        std::unordered_map<int, TimetableUnit> timetables{};
    };
}


