#include "pch.h"
#include "../JSONDatabaseCheck/src/DataChecker.h"
#include "../JSONDatabaseCheck/src/DataChecker.cpp"

namespace datachecker
{
    extern std::string testString;

    void runChecker(DataChecker& checker) {
        checker.buildMapOfLines();
        checker.findTransferlStops();
        checker.checkSpecialStops();
        checker.checkAllArrivalTimes();
        checker.onDemandCheck();
    }
    TEST(DataChecker_test, finishStops) {
        std::unordered_map<int, std::string> testFinishStops{
            {7, "Sesame Street"},
            {3, "Elm Street"},
            {6, "Sunset Boulevard"}
        };

        DataChecker checker(testString);
        runChecker(checker);
        EXPECT_EQ(checker.FinishStops, testFinishStops);

    }

    TEST(DataChecker_test, transferStops) {
        std::unordered_map<int, std::string> testTransferStops{
            {3, "Elm Street"},
            {7, "Sesame Street"},
            {6, "Sunset Boulevard"}
        };

        DataChecker checker(testString);
        runChecker(checker);
        EXPECT_EQ(checker.TransferStops, testTransferStops);

    }

    TEST(DataChecker_test, startStops) {
        std::unordered_map<int, std::string> testStartStops{
            {1, "Prospekt Avenue"},
            {2, "Pilotow Street"},
            {4, "Bourbon Street"}
        };

        DataChecker checker(testString);
        runChecker(checker);
        EXPECT_EQ(checker.StartStops, testStartStops);

    }


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
}
