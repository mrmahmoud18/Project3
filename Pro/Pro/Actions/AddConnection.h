#pragma once

#include "Action.h"

class Connection;
class Pin;

class AddConnection: public Action
{
private:
	Pin* m_InputPin;
	Pin* m_OutputPin;
	virtual void ReadActionParameters();

public:
    AddConnection(ApplicationManager *pApp);
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};
