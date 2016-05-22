#include "AdjustOffset.h"

#include "../ApplicationManager.h"

AdjustOffset::AdjustOffset(ApplicationManager *pApp): Action(pApp) {}

void AdjustOffset::ReadActionParameters()
{
    Base = pManager->GetInterface()->GetMousePosition(true);
}

void AdjustOffset::Execute()
{
    ReadActionParameters();
    while(pManager->GetInterface()->IsDragging())
    {
        std::pair<int,int> dummy = pManager->GetInterface()->GetMousePosition(true);
        pManager->GetInterface()->ShiftOffsetBy(std::pair<int,int> (Base.first-dummy.first, Base.second-dummy.second));
        Base = dummy;
        pManager->UpdateInterface();
        pManager->SyncInterface();
    }
}

void AdjustOffset::Undo() {}

void AdjustOffset::Redo() {}
