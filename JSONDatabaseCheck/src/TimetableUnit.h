#pragma once
#include <nlohmann/json.hpp>
#include <iostream>
#include <iomanip>

using json = nlohmann::json;

namespace datachecker
{
    using json = nlohmann::json;

    class TimetableUnit
    {
    public:
        int bus_id{};
        int stop_id{};
        std::string stop_name{ "" };
        int next_stop{};
        std::string stop_type{ "" };
        std::string a_time{ "" };

        friend std::ostream& operator <<(std::ostream& out, const TimetableUnit& unit);
        static const std::map<int, std::string> dict;
        bool operator==(const TimetableUnit& other);
        bool operator!=(const TimetableUnit& other);
    };

    void to_json(json& j, const TimetableUnit& t);
    void from_json(const json& j, TimetableUnit& t);
    
} // namespace datachecker
