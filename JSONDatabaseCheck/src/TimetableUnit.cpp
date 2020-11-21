#include "TimetableUnit.h"

namespace datachecker
{
    using Key = TimetableUnit::Keys;

    std::ostream& operator<<(std::ostream& out, const TimetableUnit& unit)
    {
        out << Key::BUS_ID << unit.bus_id << " \n"
            << Key::STOP_ID << unit.stop_id << " \n"
            << Key::STOP_NAME << unit.stop_name << " \n"
            << Key::NEXT_STOP << unit.next_stop << " \n"
            << Key::STOP_TYPE << unit.stop_type << " \n"
            << Key::A_TIME << unit.a_time << " \n\n";

        return out;
    }

    void datachecker::to_json(json& j, const TimetableUnit& t)
    {
        j = json{
            {Key::BUS_ID, t.bus_id},
            {Key::STOP_ID, t.stop_id},
            {Key::STOP_NAME, t.stop_name},
            {Key::NEXT_STOP, t.next_stop},
            {Key::STOP_TYPE, t.stop_type},
            {Key::A_TIME, t.a_time} };
    }

    void datachecker::from_json(const json& j, TimetableUnit& t)
    {
        j.at(Key::BUS_ID).get_to(t.bus_id);
        j.at(Key::STOP_ID).get_to(t.stop_id);
        j.at(Key::STOP_NAME).get_to(t.stop_name);
        j.at(Key::NEXT_STOP).get_to(t.next_stop);
        j.at(Key::STOP_TYPE).get_to(t.stop_type);
        j.at(Key::A_TIME).get_to(t.a_time);
    }
}

