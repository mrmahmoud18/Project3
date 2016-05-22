#pragma once
#include"Action.h"

class Validation : public Action
{
public:
	Validation(ApplicationManager *pApp);
	~Validation();
	virtual void Execute();
	virtual void ReadActionParameters();
	virtual void Undo();
	virtual void REDO();
};

