#pragma once
#include "Action.h"

class Simulate :public Action
{
public:
	Simulate(ApplicationManager * pApp);
	~Simulate();
	virtual void Execute();
	virtual void ReadActionParameters();
	virtual void Undo();
	virtual void REDO();
};

