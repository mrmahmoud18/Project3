#include "Delete.h"

#include "../ApplicationManager.h"

#include <set>

Delete::Delete(ApplicationManager *pApp) : Action(pApp) {}

void Delete::ReadActionParameters()
{
	std::set<Component*> SetSelected= pManager->GetSelectedComponents();
	std::vector<Component*> Components(SetSelected.begin(), SetSelected.end());
}

void Delete::Execute()
{
	pManager->RemoveComponents(Components);
}

void Delete::Undo()
{
	pManager->AddComponents(Components);
}

void Delete::Redo()
{
	pManager->RemoveComponents(Components);
}
