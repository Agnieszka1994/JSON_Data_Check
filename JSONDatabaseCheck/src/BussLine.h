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
		friend std::ostream& operator <<(std::ostream& out, const BussLine& unit);
	private:
		int lineId;
		int startStop{-1};
		int finalStop{-1};
		std::unordered_multimap<int,TimetableUnit> stops;
	};
}
