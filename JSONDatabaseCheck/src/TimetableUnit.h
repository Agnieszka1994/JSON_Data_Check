#pragma once
#include <nlohmann/json.hpp>
#include <iostream>

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
        
    public://static class with key shortcuts for the convenience of use
        static class Keys
        {
        public:
            static constexpr char* BUS_ID = const_cast<char* const>("bus_id");
            static constexpr char* STOP_ID = const_cast<char* const>("stop_id");
            static constexpr char* STOP_NAME = const_cast<char* const>("stop_name");
            static constexpr char* NEXT_STOP = const_cast<char* const>("next_stop");
            static constexpr char* STOP_TYPE = const_cast<char* const>("stop_type");
            static constexpr char* A_TIME = const_cast<char* const>("a_time");
        };
    };

    void to_json(json& j, const TimetableUnit& t);
    void from_json(const json& j, TimetableUnit& t);
    
} // namespace datachecker
