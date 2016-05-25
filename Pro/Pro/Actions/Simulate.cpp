#include "Simulate.h"

#include "../ApplicationManager.h"

Simulate::Simulate(ApplicationManager *pApp): Action(pApp) {}

void Simulate::ReadActionParameters() {}

void Simulate::Execute()
{
	if (!pManager->SimulateComponents())
		throw;
}

void Simulate::Undo() {}

void Simulate::Redo() {}
