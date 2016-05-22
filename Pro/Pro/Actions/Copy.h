#pragma once

#include "Action.h"

class Copy: public Action
{
private:
    virtual void ReadActionParameters();

public:
    Copy(ApplicationManager *pApp);
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};
