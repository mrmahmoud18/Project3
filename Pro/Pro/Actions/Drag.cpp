#include "Drag.h"

#include "../ApplicationManager.h"

Drag::Drag(ApplicationManager *pApp): Action(pApp) {}

void Drag::ReadActionParameters()
{
/*
    Base = pManager->GetInterface()->GetMousePosition(true);
    std::vector<Component*>& Components = pManager->GetComponents();
    for(unsigned int i = 0; i < Components.size(); i++)
    {
        if(Components[i]->GetStatus() = SELECTED)
        {
            Gate* pGate = dynamic_cast<Gate*> (Components[i]);
            if(pGate == NULL)
                Items.insert(Components[i]);
        }
    }
*/
}

void Drag::Execute()
{
    ReadActionParameters();
    pManager->GetInterface()->SetBusy(true);
    while(pManager->GetInterface()->IsDragging())
    {
        std::pair<int,int> dummy = pManager->GetInterface()->GetMousePosition(true);
        pManager->GetInterface()->ShiftOffsetBy(std::pair<int,int> (Base.first-dummy.first, Base.second-dummy.second));
        Base = dummy;
        pManager->UpdateInterface();
        pManager->GetInterface()->SetMouseStatus(Interface::NAVIGATION);
        pManager->SyncInterface();
    }
    pManager->GetInterface()->SetBusy(false);
}

void Drag::Undo() {}

void Drag::Redo() {}
