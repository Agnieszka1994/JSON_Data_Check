#include "TimetableUnit.h"
#include "DataChecker.h"


using namespace datachecker;
int main() {
    /*TimetableUnit testo{3, 5, "testowy przystanek", 66, "cos", "08:21"};
    auto a = DataChecker::members[1];
    auto b = DataChecker::members[2];
    std::cout << typeid(b).name() << std::endl;*/
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
        "stop_type" : "O",
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


    DataChecker testowy(testString);
    //testowy.printTimetables();
    testowy.buildMapOfLines();
    //testowy.printLines();
    testowy.checkSyntax();
    testowy.printLinesInfo();
    testowy.printSpecialStops();
}