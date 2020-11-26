#pragma once
#include <unordered_map>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include "DataChecker.h"


namespace datachecker
{
	const std::string WRONG_INPUT{ "Wrong input type! Please try again:\n" };

	class MainMenu
	{
	public:
		MainMenu();
		MainMenu(std::string& data);
		MainMenu(json& data);
		MainMenu(MainMenu&) = delete;
		MainMenu(MainMenu&&) = delete;

		void run();

		std::unordered_map<int, void(DataChecker::*)()> checkFunc{
			{1, &DataChecker::checkDataTypes},
			{2, &DataChecker::checkSyntax},
			{3, &DataChecker::buildMapOfLines},
			{4, &DataChecker::findTransferlStops},
			{5, &DataChecker::checkSpecialStops},
			{6, &DataChecker::printLinesInfo},
			{7, &DataChecker::printSpecialStops},
			{8, &DataChecker::checkAllArrivalTimes},
			{9, &DataChecker::onDemandCheck}
		};
		std::unordered_map<int, void(DataChecker::*)()> menuFunc{
			{1, &DataChecker::printTimetables},
			{2, &DataChecker::printLinesInfo},
			{3, &DataChecker::printSpecialStops},
			{4, &DataChecker::printTransferStops},
			{5, &DataChecker::printFinishStops},
			{6, &DataChecker::printStartStops}
		};
		template<typename T>
		static T getInput();
	private:
		void runCheck();
		void runMenuFunc();
		void displayMenu() const;
		std::string getFileName();
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