#pragma once

#include "Action.h"

#include <string>

class Component;

class AddComponent: public Action
{
private:
	ActionType m_ActionType;
	std::pair<int,int> Center;
	Component* pComp;
	virtual void ReadActionParameters();

public:
    AddComponent(ApplicationManager *pApp, Action::ActionType r_ActionType);
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};
