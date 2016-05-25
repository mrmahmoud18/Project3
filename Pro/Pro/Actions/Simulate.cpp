#include "Simulate.h"

#include "../ApplicationManager.h"

#include <iostream>

Simulate::Simulate(ApplicationManager *pApp): Action(pApp) {}

void Simulate::ReadActionParameters() {}

void Simulate::Execute()
{
	pManager->ResetComponents();
	if (!pManager->AreComponentsConnected())
    {
        std::cerr << "Circuit NOT connected" << std::endl;
        return;
    }
	if (!pManager->SimulateComponents())
	{
        std::cerr << "Infinite loop" << std::endl;
        return;
    }
    if(!pManager->GetInterface()->IsSimulating())
        pManager->GetInterface()->SwitchAppMode();
}

void Simulate::Undo() {}

void Simulate::Redo() {}
