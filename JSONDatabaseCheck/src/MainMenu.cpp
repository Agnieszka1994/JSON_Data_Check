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
			(*checker.*func)();
		}
	}

	void datachecker::MainMenu::displayMenu()
	{
	}
}

