#pragma once

#include "Action.h"

class Paste: public Action
{
private:
    virtual void ReadActionParameters();

public:
    Paste(ApplicationManager *pApp);
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};
