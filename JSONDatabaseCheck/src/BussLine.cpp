#include "BussLine.h"
namespace datachecker
{
	BussLine::BussLine(TimetableUnit t) : lineId(t.bus_id)
	{
		addTimetable(t);
		startStop = t.stop_type == "S" ? t.stop_id : -1;
		finalStop = t.stop_type == "F" ? t.stop_id : -1;
	}

	void BussLine::addTimetable(TimetableUnit t)
	{
		if (t.bus_id != lineId) {
			throw std::invalid_argument("Buss ID different from Line ID!");
		}
		else {
			stops.insert({ t.stop_id, t });
		}
	}

	std::ostream& operator<<(std::ostream& out, const BussLine& line)
	{
		std::cout << "Line nr: " << line.lineId << std::endl;
		for (auto stop : line.stops) {
			std::cout << stop.second;
		}
		return out;
	}

}
