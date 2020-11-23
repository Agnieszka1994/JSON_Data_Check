#include "DataChecker.h"
#if 1
#define LOG(a,b) std::cout<<a<<" "<<b
#endif

namespace datachecker
{
    const std::string PROCESS_TERMINATED{"\nProcess terminated\n"};
    const std::string ERRORS_FOUND{ "The following errors were found:\n" };
    const std::string CHECKING_DATA{ "Data types check... Please wait...\n" };
    const std::string DATA_TYPES_ERROR{ "Incorrect data types found! Checking aborted.\n" };
    const std::string DATA_TYPES_CORRECT{ "Data Types Correct\n" };
    const std::string CHECKING_SYNTAX{ "Syntax check...\n" };
    const std::string INCORRECT_SYNTAX{ "Incorrect Synatx!\nStop_name, Stop_type or Time format did not meet the requirements!\n" };
    const std::string SYNTAX_CORRECT{"Syntax correct!\n"};
    const std::string LINE_NAMES{ "Line names and number of stops:\n" };
    const std::string MISSING_STOP{ "There is no start or end stop for the line: " };
    const std::string TIME_TEST{ "Arrival time test:\n" };
    const std::string TIME_TEST_SUCCESS{ "Arrival times OK\n" };
    const std::string ON_DEMAND_TEST{ "On demand stops test: " };
    const std::string WRONG_STOP_TYPES{ "Wrong stop type: " };
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

    bool DataChecker::compareTimes(std::tm a, std::tm b, std::function<bool(std::tm, std::tm)> fn)
    {
        return fn(a, b);
    }

    std::tm DataChecker::convertStringToTime(std::string str)
    {
        struct std::tm tm {};
        std::istringstream ss(str);
        ss >> std::get_time(&tm, "%H:%M");
        return tm;
    }

    void DataChecker::checkAllArrivalTimes()
    {
        std::cout << TIME_TEST;
        for (auto& line : lines) {
            try{
                checkArrivalTimesForLine(line.second);
            }
            catch (const std::logic_error&){
                throw;
            }   
        }
        std::cout << TIME_TEST_SUCCESS;
    }

    void DataChecker::checkArrivalTimesForLine(BussLine& line)
    {
        
        TimetableUnit previousStop{ line.stops[line.startStop] };
        TimetableUnit currentStop{ line.stops[previousStop.next_stop] };
        while (true)
        {
            std::tm prevTime{ convertStringToTime(previousStop.a_time) };
            std::tm currTime{ convertStringToTime(currentStop.a_time) };

            auto rule = [](std::tm a, std::tm b) ->bool 
            { return (a.tm_hour < b.tm_hour) 
                || (a.tm_hour <= b.tm_hour && a.tm_min < b.tm_min); 
            };

            if (!compareTimes(prevTime, currTime, rule)) {
      
                std::string msg{ "bus_id line " + std::to_string(currentStop.bus_id)
                    + ": wrong time on station " + currentStop.stop_name };
                throw std::logic_error(msg);
            }
            try {
                previousStop = currentStop;
                currentStop = line.stops.at((currentStop.next_stop));
            }
            catch (std::out_of_range&) {
                break;
            }
        }
    }

    void DataChecker::checkSpecialStops()
    {
        for (auto line : lines) {
            if (line.second.startStop == -1 || line.second.finalStop == -1) {
                std::string msg{ MISSING_STOP + std::to_string(line.second.lineId) };
                throw std::logic_error(msg);
            }
        }
    }

    void DataChecker::onDemandCheck()
    {
        std::cout << ON_DEMAND_TEST;
        std::unordered_map<int, std::string> wrongTypeStops{};
        for (auto timetable : timetables) {
            TimetableUnit current = timetable.second;
            if(current.stop_type == "O" && (
               TransferStops.find(current.stop_id) != TransferStops.end()
            || StartStops.find(current.stop_id) != StartStops.end()
            || FinishStops.find(current.stop_id) != FinishStops.end())){
                wrongTypeStops.insert({ current.stop_id, current.stop_name });
            }
        }
        if (!wrongTypeStops.empty()) {
            std::cout << WRONG_STOP_TYPES;
            printStops(wrongTypeStops);
            throw std::logic_error("");
        }
        else{
            std::cout << "OK" << std::endl;
        }
    }

    void datachecker::DataChecker::printErrors()
    {
        std::cout << ERRORS_FOUND;
        for (auto& obj : errors) {
            for (int it = BusId; it != end; it++) {
                int currentSum{ sumOfErrorValues(obj, static_cast<Error>(it)) };
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

    void DataChecker::printSpecialStops()
    {
        printStartStops();
        printTransferStops();
        printFinishStops();
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
                catch (std::exception&) {
                    throw;
                }
            }  
        }
    }

    void DataChecker::findTransferlStops()
    {
        std::set<int> stopsTmp;
        for (const auto &line : lines) {
            for (const auto &stop : line.second.stops) {
                if (stopsTmp.find(stop.second.stop_id) == stopsTmp.end()){
                    stopsTmp.insert(stop.second.stop_id);
                }
                else{
                    TransferStops.insert({ stop.second.stop_id, stop.second.stop_name});
                }
            }
        }
    }

    void DataChecker::addStop(int id, std::string name, std::unordered_map<int, std::string>& container)
    {
        if (container.find(id) == container.end())
        {
            container.insert({ id, name });
        }
    }

    void DataChecker::addTransferStop(int id, std::string name)
    {
        if (TransferStops.find(id) == TransferStops.end())
        {
            TransferStops.insert({ id, name });
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
            // adding the current stop to the appropriate container
            if (tmp.stop_type == "F") {
                addStop(tmp.stop_id, tmp.stop_name, FinishStops);
            }
            if (tmp.stop_type == "S") {
                addStop(tmp.stop_id, tmp.stop_name, StartStops);
            }
            iterator++;
            // if no errors detected add to container "timetables"
            if (errors.empty()) {
                timetables.insert({ tmp.stop_id, tmp });
            }
        }
        if (!errors.empty()) {
            printErrors();
            throw std::invalid_argument(DATA_TYPES_ERROR);
        }
        else {
            std::cout << DATA_TYPES_CORRECT;
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
            std::cout << SYNTAX_CORRECT;
        }
    }

    void DataChecker::printStartStops()
    {
        std::cout << "Start stops: ";
        printStops(StartStops);
    }

    void DataChecker::printFinishStops()
    {
        std::cout << "Finish stops: ";
        printStops(FinishStops);
    }
    void DataChecker::printTransferStops()
    {
        std::cout << "Transfer stops: ";
        printStops(TransferStops);
    }
    void DataChecker::printStops(std::unordered_map<int, std::string> stops) {
        std::cout << stops.size() << " [";
        for (auto stop : stops) {
            std::cout << "'" << stop.second << "', ";
        }
        std::cout << "\b\b]" << std::endl;
    }
} // namespace datachecker

