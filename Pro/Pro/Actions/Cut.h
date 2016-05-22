#pragma once

#include "Action.h"

class Cut: public Action
{
private:
    virtual void ReadActionParameters();

public:
    Cut(ApplicationManager *pApp);
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};
