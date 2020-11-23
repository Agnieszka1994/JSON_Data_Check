#include "MainMenu.h"

namespace datachecker
{
	datachecker::MainMenu::MainMenu()
	{
	}

	datachecker::MainMenu::MainMenu(std::string& data)
	{
		checker->uploadData(data);
	}

	void datachecker::MainMenu::run()
	{
		for (auto& pair: menuFunc)
		{
			auto& func{ pair.second };
			try {
				(*checker.*func)();
			}
			catch (std::exception& e) {
				std::cout << e.what() << std::flush;
				break;
			}
			Sleep(1000);
		}
	}

	void datachecker::MainMenu::displayMenu()
	{
	}
}

