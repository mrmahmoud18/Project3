#include "HandleLeftClick.h"

#include "../ApplicationManager.h"
#include "../Components/Pin.h"

HandleLeftClick::HandleLeftClick(ApplicationManager *pApp): Action(pApp) {}

void HandleLeftClick::ReadActionParameters()
{
    pComp = pManager->GetComponentAt(pManager->GetInterface()->GetMousePosition());
    pPin = pManager->GetPinAt(pManager->GetInterface()->GetMousePosition());
}

void HandleLeftClick::Execute()
{
    ReadActionParameters();
    if(pManager->GetInterface()->IsDoubleClick())
    {
        printf("%s \n", "HELL YEAH!");
    }
    else if(pManager->GetInterface()->IsDragging())
    {
        printf("%s \n", "DRAGGING!");
        if(pManager->GetInterface()->IsCtrlOn())
            pManager->ExecuteAction(ADJUST_OFFSET);
        else if(pComp != NULL)
            pManager->ExecuteAction(DRAG);
        else
            pManager->ExecuteAction(MULTI_SELECT);
    }
    else
    {
        if(pPin != NULL && pPin->IsConnectable())
            pManager->ExecuteAction(ADD_CONNECTION);
        else if(pComp != NULL)
        {
            if(pManager->GetInterface()->IsCtrlOn())
                pComp->SetStatus((pComp->GetStatus() == NORMAL) ? SELECTED : NORMAL);
            else
            {
                /*
                std::vector<Component*>& Components = pManager->GetComponents();
                for(unsigned int i = 0; i < Components.size(); i++)
                    Components[i]->SetStatus(NORMAL);
                pComp->SetStatus(SELECTED);
                */
            }
        }
        else if(!(pManager->GetInterface()->IsCtrlOn()))
        {
            /*
            std::vector<Component*>& Components = pManager->GetComponents();
            for(unsigned int i = 0; i < Components.size(); i++)
                Components[i]->SetStatus(NORMAL);
            */
        }
    }
}

void HandleLeftClick::Undo() {}

void HandleLeftClick::Redo() {}
