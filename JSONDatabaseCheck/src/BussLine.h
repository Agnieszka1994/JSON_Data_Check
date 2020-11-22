#pragma once
#include<set>
#include "TimetableUnit.h"

namespace datachecker
{
	class BussLine
	{
	public:
		BussLine() = delete;
		BussLine(TimetableUnit);
		void addTimetable(TimetableUnit t);
		void printLineInfo();
		friend std::ostream& operator <<(std::ostream& out, const BussLine& unit);
		int lineId;
		int startStop{-1};
		int finalStop{-1};
		std::unordered_map<int,TimetableUnit> stops;
	};
}
