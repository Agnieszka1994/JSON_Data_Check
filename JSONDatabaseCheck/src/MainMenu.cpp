#include "MainMenu.h"
#include "ConsoleClear.h"

namespace datachecker
{
	const std::string ENTER_FILE{ "Please enter file name:\n" };
	const std::string NO_OPTION{ "No such option available!\n" };
	const std::string FILE_EXTENSION{ "File extension missing or incorrect!\n" };

	datachecker::MainMenu::MainMenu()
	{
	}

	datachecker::MainMenu::MainMenu(std::string& data)
	{
		checker->uploadData(data);
	}

	MainMenu::MainMenu(json& data)
	{
		checker->uploadData(data);
	}

	void datachecker::MainMenu::runCheck()
	{
		for (auto& pair: checkFunc)
		{
			auto& func{ pair.second };
			try {
				(*checker.*func)();
			}
			catch (std::exception& e) {
				std::cout << e.what() << std::flush;
				throw;
			}
		}
	}

	void MainMenu::runMenuFunc()
	{
		int choice = getInput<int>();
		if (menuFunc.find(choice) != menuFunc.end()) {
			auto& func{ menuFunc.at(choice) };
			try {
				(*checker.*func)();
			}
			catch (std::exception&) {

			}
		}
		else {
			std::cout << NO_OPTION;
		}
	}

	void MainMenu::run() // to be refactored !!!! 
	{
		std::cout << ENTER_FILE << std::flush;
		std::string file = getFileName();
		std::ifstream jsonFile;
		jsonFile.open(file, std::ifstream::in);
		if (!jsonFile.is_open()) {
			std::cout << "File cannot be opened" << std::endl;
			//ERROR 
		}
		else {
			json jsonObj;
			jsonFile >> jsonObj;
			checker->uploadData(jsonObj);
			try {
				runCheck();
			}
			catch (std::exception) {
				exit(-1);
			}
			jsonFile.close();
			std::cout << "\nAll check passed!!!\n" << std::endl;
			std::cin.ignore(INT_MAX, '\n');
			std::cin.get();
			while (true) {
				Clear();
				displayMenu();
				runMenuFunc();
				std::cin.ignore(INT_MAX, '\n');
				std::cin.get();
			}
		}
	}

	void datachecker::MainMenu::displayMenu() const
	{
		std::cout << "What would you like to display?" << std::endl;
		std::cout << "1. All timetables" << std::endl;
		std::cout << "2. Lines info" << std::endl;
		std::cout << "3. All Special Stops" << std::endl;
		std::cout << "4. Transfer Stops" << std::endl;
		std::cout << "5. Finish Stops" << std::endl;
		std::cout << "6. Start Stops" << std::endl;
		std::cout << "0. Exit" << std::endl;
	}
	std::string MainMenu::getFileName()
	{
		std::string input = getInput<std::string>();
		while (input.find(".json") != (input.size() - 5) || input.find(".json") == std::string::npos)
		{
			std::cout << FILE_EXTENSION;
			input = getInput<std::string>();
		}
		return input;
	}
}

