#include "TimetableUnit.h"

namespace datachecker
{
	const std::map<int, std::string> TimetableUnit::dict
	{
		{0, "bus_id"},
		{ 1, "stop_id" },
		{ 2, "stop_name" },
		{ 3, "next_stop" },
		{ 4, "stop_type" },
		{ 5, "a_time" }
	};
	std::ostream& operator<<(std::ostream& out, const TimetableUnit& unit)
	{
		out << std::setw(12) << std::string(TimetableUnit::dict.at(0)) + ": " << std::setw(12) << std::left << unit.bus_id << " \n"
			<< std::setw(12) << std::string(TimetableUnit::dict.at(1)) + ": " << std::setw(12) << std::left << unit.stop_id << " \n"
			<< std::setw(12) << std::string(TimetableUnit::dict.at(2)) + ": " << std::setw(12) << std::left << unit.stop_name << " \n"
			<< std::setw(12) << std::string(TimetableUnit::dict.at(3)) + ": " << std::setw(12) << std::left << unit.next_stop << " \n"
			<< std::setw(12) << std::string(TimetableUnit::dict.at(4)) + ": " << std::setw(12) << std::left << unit.stop_type << " \n"
			<< std::setw(12) << std::string(TimetableUnit::dict.at(5)) + ": " << std::setw(12) << std::left << unit.a_time << " \n\n";

		return out;
	}

	void datachecker::to_json(json& j, const TimetableUnit& t)
	{
		j = json{
			{TimetableUnit::dict.at(0), t.bus_id},
			{TimetableUnit::dict.at(1), t.stop_id},
			{TimetableUnit::dict.at(2), t.stop_name},
			{TimetableUnit::dict.at(3), t.next_stop},
			{TimetableUnit::dict.at(4), t.stop_type},
			{TimetableUnit::dict.at(5), t.a_time} };
	}

	void datachecker::from_json(const json& j, TimetableUnit& t)
	{
		j.at(TimetableUnit::dict.at(0)).get_to(t.bus_id);
		j.at(TimetableUnit::dict.at(1)).get_to(t.stop_id);
		j.at(TimetableUnit::dict.at(2)).get_to(t.stop_name);
		j.at(TimetableUnit::dict.at(3)).get_to(t.next_stop);
		j.at(TimetableUnit::dict.at(4)).get_to(t.stop_type);
		j.at(TimetableUnit::dict.at(5)).get_to(t.a_time);
	}
	bool TimetableUnit::operator==(const TimetableUnit& other)
	{
		return stop_id == other.stop_id;
	}
	bool TimetableUnit::operator!=(const TimetableUnit& other)
	{
		return stop_id != other.stop_id;;
	}
}

