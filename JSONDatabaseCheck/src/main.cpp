
#include "TimetableUnit.h"
#include "DataChecker.h"

using namespace datachecker;
int main() {

    std::string testString = R"###([
    {
        "bus_id": 128,
        "stop_id" : 1,
        "stop_name" : "Prospekt Avenue",
        "next_stop" : 3,
        "stop_type" : "S",
        "a_time" : "08:23"
    },
    {
        "bus_id": 128,
        "stop_id" : 3,
        "stop_name" : "Elm Street",
        "next_stop" : 5,
        "stop_type" : "O",
        "a_time" : "08:23"
    },
    {
        "bus_id": 128,
        "stop_id" : 5,
        "stop_name" : "Fifth Avenue",
        "next_stop" : 7,
        "stop_type" : "O",
        "a_time" : "08:23"
    },
    {
        "bus_id": 128,
        "stop_id" : 7,
        "stop_name" : "Sesame Street",
        "next_stop" : 0,
        "stop_type" : "F",
        "a_time" : "08:23"
    },
    {
        "bus_id": 256,
        "stop_id" : 2,
        "stop_name" : "Pilotow Street",
        "next_stop" : 3,
        "stop_type" : "S",
        "a_time" : "08:23"
    },
    {
        "bus_id": 256,
        "stop_id" : 3,
        "stop_name" : "Elm Street",
        "next_stop" : 6,
        "stop_type" : "F",
        "a_time" : "08:23"
    },
    {
        "bus_id": 256,
        "stop_id" : 6,
        "stop_name" : "Sunset Boulevard",
        "next_stop" : 7,
        "stop_type" : "O",
        "a_time" : "08:23"
    },
    {
        "bus_id": 256,
        "stop_id" : 7,
        "stop_name" : "Sesame Street",
        "next_stop" : 0,
        "stop_type" : "F",
        "a_time" : "08:23"
    },
    {
        "bus_id": 512,
        "stop_id" : 4,
        "stop_name" : "Bourbon Street",
        "next_stop" : 6,
        "stop_type" : "S",
        "a_time" : "08:23"
    },
    {
        "bus_id": 512,
        "stop_id" : 6,
        "stop_name" : "Sunset Boulevard",
        "next_stop" : 0,
        "stop_type" : "F",
        "a_time" : "08:23"
    }
    ])###";


    //json series = json::parse(testString);
    ////vector<TimetableUnit> time_vec(series);
    //for (auto j : series) {
    //    TimetableUnit tmp{
    //        j["bus_id"].get<decltype(TimetableUnit::bus_id)>(),
    //        j["stop_id"].get<decltype(TimetableUnit::stop_id)>(),
    //        j["stop_name"].get<decltype(TimetableUnit::stop_name)>(),
    //        j["next_stop"].get<decltype(TimetableUnit::next_stop)>(),
    //        j["stop_type"].get<decltype(TimetableUnit::stop_type)>(),
    //        j["a_time"].get<decltype(TimetableUnit::a_time)>()
    //    };
    //    std::cout << tmp << std::endl;
    //    //std::cout << timetable.get<TimetableUnit>() << std::endl;
    //}

    DataChecker testowy(testString);

    //std::cout << series;

}//