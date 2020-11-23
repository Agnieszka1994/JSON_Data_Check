#include "MainMenu.h"
#include "ConsoleClear.h"

namespace datachecker
{
	const std::string ENTER_FILE{ "Please enter file name:\n" };
	const std::string NO_OPTION{ "No such option available!\n" };

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

	void MainMenu::runMenuFunc(int option)
	{
		if (menuFunc.find(option) != menuFunc.end()) {
			auto& func{ menuFunc.at(option) };
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
		std::string file = getInput<std::string>();
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
				int choice = getInput<int>();
				runMenuFunc(choice);
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
}

