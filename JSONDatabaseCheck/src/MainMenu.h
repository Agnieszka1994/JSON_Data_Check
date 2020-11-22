#pragma once
#include <unordered_map>
#include "DataChecker.h"

namespace datachecker
{
	class MainMenu
	{
	public:
		MainMenu(MainMenu&) = delete;
		MainMenu(MainMenu&&) = delete;

		//std::unique_ptr<DataChecker>
		// create ptr to datachecker
		// get filename from input
		// upload data from file to datachecker
		// run the checks
		// if checks completed - display options: buss lines info, print timetables
		// display info on a given line number
		
	std::unordered_map<int, void (DataChecker::*)()> mainMenu{
			{1, &DataChecker::checkDataTypes},
			{2, &DataChecker::checkSyntax},
			{3, nullptr},
			{4, nullptr},
			{5, nullptr},
			{6, nullptr},
			{0, nullptr}
		};
	};
}