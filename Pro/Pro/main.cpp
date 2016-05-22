
#include <iostream>
#include <sstream>
#include <cmath>

#include "ApplicationManager.h"

int main()
{
	Action::ActionType ActType;
	//Create an object of ApplicationManager
	ApplicationManager AppManager;

	do
	{
		//Read user action
		ActType = AppManager.GetUserAction();

		//Execute the action
		AppManager.ExecuteAction(ActType);

		//Update the drawing window
		AppManager.UpdateInterface();
		AppManager.SyncInterface();
	}while(ActType != Action::EXIT);
	return 0;
}
