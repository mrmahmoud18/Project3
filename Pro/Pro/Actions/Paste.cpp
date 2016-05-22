#include "Paste.h"

#include "../ApplicationManager.h"

Paste::Paste(ApplicationManager *pApp): Action(pApp) {}

void Paste::ReadActionParameters()
{
	Clipboard = pManager->GetClipboard();
}

void Paste::Execute()
{
	std::pair<int, int> MaxUpAndLeft(Clipboard[0]->GetCenter());
	std::pair<int, int> MaxDownAndRight(Clipboard[0]->GetCenter());
	for (unsigned int i = 0; i < Clipboard.size(); i++)
	{
		if (Clipboard[i]->GetCenter().first<MaxUpAndLeft.first&&Clipboard[i]->GetCenter().second>MaxUpAndLeft.second)
			MaxUpAndLeft = Clipboard[i]->GetCenter();
		if (Clipboard[i]->GetCenter().first>MaxDownAndRight.first&&Clipboard[i]->GetCenter().second<MaxDownAndRight.second)
			MaxDownAndRight = Clipboard[i]->GetCenter();
	}
	std::pair<int, int> Center((MaxDownAndRight.first - MaxUpAndLeft.first) / 2, (MaxUpAndLeft.second - MaxDownAndRight.second / 2));
	for (unsigned int i = 0; i < Clipboard.size(); i++)
	{
		Clipboard[i]->ShiftBy(std::pair<int, int>(Center.first - pManager->GetInterface()->GetMousePosition().first, Center.second - pManager->GetInterface()->GetMousePosition().second));
	}
	pManager->AddComponents(Clipboard);
}

void Paste::Undo()
{
    ///TODO
}

void Paste::Redo()
{
    ///TODO
}
