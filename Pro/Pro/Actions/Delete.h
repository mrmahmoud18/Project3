#pragma once

#include "Action.h"

#include<vector>

class Component;

class Delete : public Action
{
private:
	virtual void ReadActionParameters();
	std::vector<Component*> Components;

public:
	Delete(ApplicationManager *pApp);
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};
