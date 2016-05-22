#pragma once

#include "Grid.h"
#include "Clipboard.h"
#include "GUI/Interface.h"
#include "Actions/Action.h"

#include <vector>

class Component;

class ApplicationManager
{
private:
    Grid SimGrid;
    Clipboard MainClipboard;
    Interface MainInterface;
    std::vector<Component*> Components;

public:
	ApplicationManager();
	~ApplicationManager();
	Action::ActionType GetUserAction();
	void ExecuteAction(Action::ActionType Act);
	void UpdateInterface();
	void SyncInterface();
	Grid* GetGrid();
	Clipboard* GetClipboard();
	Interface* GetInterface();
	std::vector<Component*>& GetComponents();
};
