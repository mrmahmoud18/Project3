#include "Drag.h"

#include "../ApplicationManager.h"

Drag::Drag(ApplicationManager *pApp): Action(pApp) {}

void Drag::ReadActionParameters()
{
/*
    Base = pManager->GetInterface()->GetMousePosition(true);
    Components = pManager->GetSelectedComponents();
    for(std::set<Component*>::iterator i = Components.begin(); i != Components.end(); i++)
    {
        Connection* dummy = dynamic_cast<Connection*>(*i);
        if (dummy != NULL)
            Connections.insert(dummy);
    }
*/
}

void Drag::Execute()
{
    ReadActionParameters();
    pManager->GetInterface()->SetBusy(true);
    while(pManager->GetInterface()->IsDragging())
    {
        std::pair<int,int> dummy = pManager->GetInterface()->GetMousePosition();
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
