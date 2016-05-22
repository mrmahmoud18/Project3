#include "Cut.h"

#include <vector>

#include "../ApplicationManager.h"
#include "../Components/Connection.h"

Cut::Cut(ApplicationManager *pApp): Action(pApp) {}

void Cut::ReadActionParameters()
{
	std::vector<Component*> dummyClipboard = pManager->GetClipboard();
	for (unsigned int i = 0; i < dummyClipboard.size(); i++)
	{
		delete dummyClipboard[i];
	}
	pManager->FlushClipboard();
	Components = pManager->GetSelectedComponents();
}

void Cut::Execute()
{
	ReadActionParameters();
	for (std::set<Component*>::iterator i = Components.begin(); i != Components.end(); i++)
	{
		if (dynamic_cast<Connection*>(*i) == NULL)
		{
			pManager->PushIntoClipboard(*i);
		}
	}
	pManager->RemoveComponents(std::vector<Component*>(Components.begin(), Components.end()));
}

void Cut::Undo()
{
	pManager->AddComponents(std::vector<Component*>(Components.begin(), Components.end()));
	pManager->FlushClipboard();
}

void Cut::Redo()
{
	for (std::set<Component*>::iterator i = Components.begin(); i != Components.end(); i++)
	{
		if (dynamic_cast<Connection*>(*i) != NULL)
		{
			pManager->PushIntoClipboard(*i);
		}
	}
	pManager->RemoveComponents(std::vector<Component*>(Components.begin(), Components.end()));
}
