#include "../JSONDatabaseCheck/src/MainMenu.h"

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
        "stop_type" : "",
        "a_time" : "08:27"
    },
    {
        "bus_id": 128,
        "stop_id" : 5,
        "stop_name" : "Fifth Avenue",
        "next_stop" : 7,
        "stop_type" : "",
        "a_time" : "08:35"
    },
    {
        "bus_id": 128,
        "stop_id" : 7,
        "stop_name" : "Sesame Street",
        "next_stop" : 0,
        "stop_type" : "F",
        "a_time" : "08:50"
    },
    {
        "bus_id": 256,
        "stop_id" : 2,
        "stop_name" : "Pilotow Street",
        "next_stop" : 3,
        "stop_type" : "S",
        "a_time" : "08:15"
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
        "stop_type" : "",
        "a_time" : "08:45"
    },
    {
        "bus_id": 256,
        "stop_id" : 7,
        "stop_name" : "Sesame Street",
        "next_stop" : 0,
        "stop_type" : "",
        "a_time" : "09:12"
    },
    {
        "bus_id": 512,
        "stop_id" : 4,
        "stop_name" : "Bourbon Street",
        "next_stop" : 6,
        "stop_type" : "S",
        "a_time" : "08:13"
    },
    {
        "bus_id": 512,
        "stop_id" : 6,
        "stop_name" : "Sunset Boulevard",
        "next_stop" : 0,
        "stop_type" : "F",
        "a_time" : "08:16"
    }
    ])###";

    MainMenu menu;
    menu.run();

}