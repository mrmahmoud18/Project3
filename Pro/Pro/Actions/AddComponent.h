#pragma once

#include "Action.h"
#include "../Enums.h"

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
    AddComponent(ApplicationManager *pApp, ActionType r_ActionType);
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};
