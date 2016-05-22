#pragma once
#include"Action.h"

class Validation : public Action
{
private:
	virtual void ReadActionParameters();
public:
	Validation(ApplicationManager *pApp);
	~Validation();
	virtual void Execute();
	virtual void Undo();
	virtual void REDO();
};

