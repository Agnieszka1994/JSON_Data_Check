#include "BussLine.h"
namespace datachecker
{
	const std::string BUSS_ID{ "Buss ID different from Line ID!\n" };
	const std::string LOGIC_ERROR{ "More than 1 start/final stop! \n" };
	BussLine::BussLine(TimetableUnit t) : lineId(t.bus_id)
	{
		addTimetable(t);
		startStop = t.stop_type == "S" ? t.stop_id : -1;
		finalStop = t.stop_type == "F" ? t.stop_id : -1;
	}

	void BussLine::addTimetable(TimetableUnit t)
	{
		if (t.bus_id != lineId) {
			throw std::invalid_argument(BUSS_ID);
		}
		else if (startStop != -1 && t.stop_type == "S" || finalStop != -1 && t.stop_type == "F") {
			throw std::logic_error(LOGIC_ERROR);
		}
		else {
			stops.insert({ t.stop_id, t });
			startStop = startStop == -1 && t.stop_type == "S" ? t.stop_id : startStop;
			finalStop = finalStop == -1 && t.stop_type == "F" ? t.stop_id : finalStop;
		}
	}

	void BussLine::printLineInfo()
	{
		std::cout << TimetableUnit::dict.at(0) << ": " << lineId
			<< ", stops: " << stops.size() << std::endl;
	}

	std::ostream& operator<<(std::ostream& out, const BussLine& line)
	{
		std::cout << TimetableUnit::dict.at(0) << " " << line.lineId << std::endl;
		for (auto stop : line.stops) {
			std::cout << stop.second;
		}
		return out;
	}

}
