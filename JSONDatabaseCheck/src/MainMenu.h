#pragma once
#include <unordered_map>
#include "DataChecker.h"

namespace datachecker
{
	const std::string WRONG_INPUT{ "Wrong input type! Please try again:\n" };

	class MainMenu
	{
	public:
		MainMenu();
		MainMenu(std::string& data);
		MainMenu(MainMenu&) = delete;
		MainMenu(MainMenu&&) = delete;
		
		void run();

		//std::unique_ptr<DataChecker>
		// create ptr to datachecker
		// get filename from input
		// upload data from file to datachecker
		// run the checks
		// if checks completed - display options: buss lines info, print timetables
		// display info on a given line number
	
		void displayMenu();
		std::unordered_map<int, void(DataChecker::*)()> menuFunc{
			{1, &DataChecker::checkDataTypes},
			{2, &DataChecker::checkSyntax},
			{3, &DataChecker::buildMapOfLines},
			{4, &DataChecker::findTransferlStops},
			{5, &DataChecker::printLinesInfo},
			{6, &DataChecker::printSpecialStops}

			//{5, nullptr}
		
		};

		template<typename T>
		static T getInput();
	private:
		std::unique_ptr<DataChecker> checker = std::make_unique<DataChecker>();
	};

	template<typename T>
	inline T MainMenu::getInput()
	{
		T input;
		std::cin >> input;
		// error check
		while (std::cin.good() == false) {
			// clear stream
			std::cout << WRONG_INPUT << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			// get input again		
			std::cin >> input;
		}
		return input;
	}
}