#include "DataChecker.h"


namespace datachecker
{
    const std::string PROCESS_TERMINATED{"\nProcess terminated\n"};
    const std::string ERRORS_FOUND{ "The following errors were found:\n" };
    const std::string CHECKING_DATA{ "Data types check... Please wait...\n" };
    const std::string DATA_TYPES_ERROR{ "Incorrect data types found! Checking aborted.\n" };
    const std::string DATA_TYPES_CORRECT{ "Data Types Correct\n" };
    const std::string CHECKING_SYNTAX{ "Syntax check...\n" };
    const std::string INCORRECT_SYNTAX{ "Incorrect Synatx!\n Stop_name, Stop_type or Time format did not meet the requirements!\n" };
    const std::string SYNTAX_CORRECT{"Syntax correct!\n"};
    const std::string LINE_NAMES{ "Line names and number of stops:\n" };

    datachecker::DataChecker::DataChecker(std::string& data)
    {
        uploadData(data);
        checkDataTypes();
    }

    void datachecker::DataChecker::insertError(int objId, Error e)
    {
        try {
            errors.at(objId).push_back(e);
        }
        catch (std::out_of_range) {
            errors.insert({ objId, std::vector<Error>{e} });
        }
    }

    void DataChecker::uploadData(std::string& data)
    {
        series = json::parse(data);
    }

    void datachecker::DataChecker::printErrors()
    {
        std::cout << ERRORS_FOUND;
        for (auto& obj : errors) {
            for (int it = BusId; it != end; it++) {
                int currentSum = sumOfErrorValues(obj, static_cast<Error>(it));
                if (currentSum) {
                    std::cout << "Obj " << obj.first << " : ";
                    std::cout << TimetableUnit::dict.at(it) << std::endl;
                }
            }
        }
    }

    void DataChecker::printTimetables()
    {
        for (auto& pair : timetables) {
            std::cout << pair.second << std::endl;
        }
    }

    void DataChecker::printLinesInfo()
    {
        std::cout << LINE_NAMES;
        for (auto& line : lines) {
            line.second.printLineInfo();
        }
    }

    int datachecker::DataChecker::sumOfErrorValues(const std::pair<int, std::vector<Error>>& obj, Error errorValue)
    {
        return std::count_if(obj.second.begin(), obj.second.end(), [&errorValue](Error e) { return e == errorValue; });
    }

    void DataChecker::buildMapOfLines()
    {
        for (auto& timetable : timetables) {
            // if current line is not on the list
            if (lines.find(timetable.second.bus_id) == lines.end()) {
                lines.insert({ timetable.second.bus_id, BussLine(timetable.second) });
            }
            else {
                try {
                    lines.at(timetable.second.bus_id).addTimetable(timetable.second);
                }
                catch (std::exception& e) {
                    std::cout << e.what();
                    break; 
                }
            }  
        }
    }

    void DataChecker::tryToAssign(json& j, TimetableUnit& tmp, const int& iterator)
    {
        // try to get buss id from JSON input
        try {
            tmp.bus_id = j[TimetableUnit::dict.at(0)].get<decltype(TimetableUnit::bus_id)>();

        }
        catch (...) {
            insertError(iterator, BusId);
        }
        // try to get stop id from JSON input
        try {
            tmp.stop_id = j[TimetableUnit::dict.at(1)].get<decltype(TimetableUnit::stop_id)>();
        }
        catch (...) {
            insertError(iterator, StopId);
        }
        // try to get stop name from JSON input
        try {
            tmp.stop_name = j[TimetableUnit::dict.at(2)].get<decltype(TimetableUnit::stop_name)>();
        }
        catch (...) {
            insertError(iterator, StopName);
        }
        // try to get next stop id from JSON input
        try {
            tmp.next_stop = j[TimetableUnit::dict.at(3)].get<decltype(TimetableUnit::next_stop)>();
        }
        catch (...) {
            insertError(iterator, NextStop);
        }
        // try to get stop type from JSON input
        try {
            tmp.stop_type = j[TimetableUnit::dict.at(4)].get<decltype(TimetableUnit::stop_type)>();
        }
        catch (...) {
            insertError(iterator, StopType);
        }
        // try to get a time from JSON input
        try {
            tmp.a_time = j[TimetableUnit::dict.at(5)].get<decltype(TimetableUnit::a_time)>();
        }
        catch (...) {
            insertError(iterator, Time);
        }
    }

    void datachecker::DataChecker::checkDataTypes()
    {
        std::cout << CHECKING_DATA;
        int iterator{ 0 };
        // iterate through the JSON object and try to build TimetableUnit objects
        for (auto j : series) {
            TimetableUnit tmp;
            tryToAssign(j, tmp, iterator);
            iterator++;
            if (errors.empty()) {
                timetables.insert({ tmp.stop_id, tmp });
            }
        }
        if (!errors.empty()) {
            printErrors();
            throw std::invalid_argument(DATA_TYPES_ERROR);
        }
    }
    void DataChecker::checkSyntax()
    {
        for (auto timetable : timetables) {
            if (!std::regex_match(timetable.second.stop_name, std::regex("^[A-Z][A-Za-z ]+ (Road|Avenue|Boulevard|Street)$"))) {
                insertError(timetable.first, StopName);
            }
            if (!std::regex_match(timetable.second.stop_type, std::regex("^[SOF]$|^$"))) {
                insertError(timetable.first, StopName);
            }
            if (!std::regex_match(timetable.second.a_time, std::regex("^(0[1-9]|1[0-9]|2[0-3]):[0-5][0-9]$"))) {
                insertError(timetable.first, StopName);
            }
        }
        if (!errors.empty()) {
            printErrors();
            throw std::invalid_argument(INCORRECT_SYNTAX);
        }
        else {
            std::cout << SYNTAX_CORRECT << std::endl;
        }
    }
} // namespace datachecker

