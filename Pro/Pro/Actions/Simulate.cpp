#include "Simulate.h"
#include "../ApplicationManager.h"


Simulate::Simulate(ApplicationManager * pApp)
	:Action(pApp)
{
}

Simulate::~Simulate()
{
}

void Simulate::Execute()
{
	if (!pManager->Simulate())
	{
		throw;
	} 
}

void Simulate::ReadActionParameters()
{
}

void Simulate::Undo()
{
}

void Simulate::REDO()
{
}
