#pragma once
#include "Action.h"

class Simulate :public Action
{
private:
	virtual void ReadActionParameters();
public:
	Simulate(ApplicationManager * pApp);
	~Simulate();
	virtual void Execute();
	virtual void Undo();
	virtual void REDO();
};

