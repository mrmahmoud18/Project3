#pragma once

#include "Action.h"

#include <set>

class Component;

class Drag: public Action
{
private:
    std::pair<int,int> Base;
    std::set<Component*> Items;
    virtual void ReadActionParameters();

public:
    Drag(ApplicationManager *pApp);
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};
