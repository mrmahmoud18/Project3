#pragma once

#include "Enums.h"
#include "Grid.h"
#include "GUI/Interface.h"
#include "Actions/Action.h"

#include <vector>
#include <set>

class Component;
class Pin;

class ApplicationManager
{
private:
    Grid SimGrid;
    std::vector<Component*> Clipboard;
    Interface MainInterface;
    std::vector<Component*> Components;

public:
	ApplicationManager();
	~ApplicationManager();
	ActionType GetUserAction();
	void ExecuteAction(ActionType Act);
	void UpdateInterface();
	void SyncInterface();
	Interface* GetInterface();

	bool IsClipboardEmpty() const;
	void PushIntoClipboard(Component* ToBeSaved);
	const std::vector<Component*>& GetClipboard();
	void FlushClipboard();

	std::vector< std::pair<int,int> > FindPathThroughGrid(std::pair<int,int> Point1, std::pair<int,int> Point2);
	bool IsValidCenter(std::pair<int,int> Center) const;
	Component* GetComponentAt(std::pair<int, int> Point);
	Pin* GetPinAt(std::pair<int, int> Point);

	std::set<Component*> GetSelectedComponents();
	void AddComponents(const std::vector<Component*>& ToBeAdded);
	void RemoveComponents(const std::vector<Component*>& ToBeRemoved);
};
