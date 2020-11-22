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
        void printSpecialStops();
        static std::map<Error, const char*> dict;
        //static std::map<int, std::any*> members;

    public:
        void checkSpecialStops();
        void buildMapOfLines();
        void buildTransferlStops(); // transfer stops to be added
        void addStop(int id, std::string name, std::unordered_map<int, std::string>& container);
        void addTransferStop(int id, std::string name);
        void checkDataTypes();
        void checkSyntax();

    private:
        void printStartStops();
        void printFinishStops();
        void printTransferStops();
        void printStops(std::unordered_map<int, std::string> stops);
        void tryToAssign(json& j, TimetableUnit& t, const int& iterator);
        void insertError(int objId, Error e);
        int sumOfErrorValues(const std::pair<int, std::vector<Error>>& obj, Error errorValue);
        std::unordered_map<int, std::vector<Error>> errors{};
        std::unordered_multimap<int, TimetableUnit> timetables{};
        std::unordered_map<int, BussLine> lines{};
        std::unordered_map<int, std::string> StartStops{};
        std::unordered_map<int, std::string> FinishStops{};
        std::unordered_map<int, std::string> TransferStops{};
        //the below should be put inside the function
        //std::unordered_map<int, std::pair<std::string, int>> transferStops{};
        json series;
    };
}


