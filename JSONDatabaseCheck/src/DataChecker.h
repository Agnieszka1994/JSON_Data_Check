#pragma once
#include "TimetableUnit.h"
#include "BussLine.h"
#include <numeric>
#include <stdexcept>
#include <regex>
#include <set>
#include <any>

namespace datachecker
{
    class DataChecker
    {
    public:
        DataChecker() = default;
        DataChecker(DataChecker&) = delete;
        DataChecker(DataChecker&&) = delete;
        DataChecker(std::string&);

        enum Error { BusId, StopId, StopName, NextStop, StopType, Time, end };
        void uploadData(std::string& data); // check data types
        void printErrors();
        void printTimetables();
        void printLinesInfo();

        static std::map<Error, const char*> dict;
        //static std::map<int, std::any*> members;

    public:
        void buildMapOfLines();
        
        void checkDataTypes();
        void checkSyntax();

    private:
        void tryToAssign(json& j, TimetableUnit& t, const int& iterator);
        void insertError(int objId, Error e);
        int sumOfErrorValues(const std::pair<int, std::vector<Error>>& obj, Error errorValue);
        std::unordered_map<int, std::vector<Error>> errors{};
        std::unordered_multimap<int, TimetableUnit> timetables{};
        std::unordered_map<int, BussLine> lines{};
        json series;
    };
}


