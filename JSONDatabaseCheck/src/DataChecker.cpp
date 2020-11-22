#include "DataChecker.h"
#include <numeric>
#include <stdexcept>

namespace datachecker
{
    const std::string PROCESS_TERMINATED{"Process terminated"};

    datachecker::DataChecker::DataChecker(std::string& data)
    {
        checkDataTypes(data);
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

    void datachecker::DataChecker::printErrors()
    {
        std::cout << "The following errors were found:\n";
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

    void DataChecker::printLines()
    {
        for (auto& pair : lines) {
            std::cout << pair.second << std::endl;
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
                catch (std::logic_error) {
                    std::cout << PROCESS_TERMINATED << std::endl;
                    break;
                    ///
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

    void datachecker::DataChecker::checkDataTypes(std::string& data)
    {
        json series = json::parse(data);
        //vector<TimetableUnit> time_vec(series);
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
        }
    }
} // namespace datachecker

