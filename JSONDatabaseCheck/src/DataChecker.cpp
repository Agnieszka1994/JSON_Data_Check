#include "DataChecker.h"
#include <numeric>
#include <stdexcept>
#if 1
#define LOG(x,y) std::cout <<x<<"__"<<y<< std::endl;
#else
#endif // 0

namespace datachecker
{
    using Key = TimetableUnit::Keys;

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
            std::cout << "Obj ID: " << obj.first << std::endl;
            std::cout << Key::BUS_ID << sumOfErrorValues(obj, BusId) << "\n"
                << Key::STOP_ID << sumOfErrorValues(obj, StopId) << "\n"
                << Key::STOP_NAME << sumOfErrorValues(obj, StopName) << "\n"
                << Key::NEXT_STOP << sumOfErrorValues(obj, NextStop) << "\n"
                << Key::STOP_TYPE << sumOfErrorValues(obj, StopType) << "\n"
                << Key::A_TIME << sumOfErrorValues(obj, Time) << "\n\n";
        }
    }

    int datachecker::DataChecker::sumOfErrorValues(const std::pair<int, std::vector<Error>>& obj, Error errorValue)
    {
        return std::count_if(obj.second.begin(), obj.second.end(), [&errorValue](Error e) { return e == errorValue; });
    }


    void datachecker::DataChecker::checkDataTypes(std::string& data)
    {
        json series = json::parse(data);
        //vector<TimetableUnit> time_vec(series);
        int iterator{ 0 };
        // iterate through the JSON object and try to build TimetableUnit objects
        for (auto j : series) {
            TimetableUnit tmp;
            // try to get buss id from JSON input
            try {
                tmp.bus_id = j[Key::BUS_ID].get<decltype(TimetableUnit::bus_id)>();
                
            }
            catch (...) {
                insertError(iterator, BusId);
                LOG(iterator, tmp.bus_id)
            }
            // try to get stop id from JSON input
            try {
                tmp.stop_id = j[Key::STOP_ID].get<decltype(TimetableUnit::stop_id)>();
            }
            catch (...) {
                insertError(iterator, StopId);
                LOG(iterator, tmp.stop_id)
            }
            // try to get stop name from JSON input
            try {
                tmp.stop_name = j[Key::STOP_NAME].get<decltype(TimetableUnit::stop_name)>();
            }
            catch (...) {
                insertError(iterator, StopName);
                LOG(iterator, tmp.stop_name)
            }
            // try to get next stop id from JSON input
            try {
                tmp.next_stop = j[Key::NEXT_STOP].get<decltype(TimetableUnit::next_stop)>();
            }
            catch (...) {
                insertError(iterator, NextStop);
                LOG(iterator, tmp.next_stop)
            }
            // try to get stop type from JSON input
            try {
                tmp.stop_type = j[Key::STOP_TYPE].get<decltype(TimetableUnit::stop_type)>();
            }
            catch (...) {
                insertError(iterator, StopType);
                LOG(iterator, tmp.stop_type)
            }
            // try to get a time from JSON input
            try {
                tmp.a_time = j[Key::A_TIME].get<decltype(TimetableUnit::a_time)>();
            }
            catch (...) {
                insertError(iterator, Time);
                LOG(iterator, tmp.a_time)
            }

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

