#include "Add.h"

#include "../ApplicationManager.h"
#include "../GUI/Button.h"

Add::Add(ApplicationManager *pApp): Action(pApp) {}

void Add::ReadActionParameters() {}

void Add::Execute()
{
    std::vector<Button*> Buttons = pManager->GetInterface()->GetActiveButtons();
    std::vector<Button*> Gates = pManager->GetInterface()->GetGatesButtons();
    std::pair<int,int> dummy;
    ActionType Act = NONE;
    for(unsigned int i = 0; i < Buttons.size(); i++)
        if(Buttons[i] != NULL)
            if(Buttons[i]->GetAction() == ADD)
            {
                Buttons[i]->SetStatus(Button::PRESSED);
                break;
            }
    pManager->GetInterface()->SetBusy(true);
    pManager->UpdateInterface();
    pManager->GetInterface()->SetBusy(false);
    pManager->GetInterface()->DrawGatesBars();
    pManager->SyncInterface();
    do
    {
        dummy = pManager->GetInterface()->GetInstantClick(true);
        pManager->GetInterface()->SetBusy(true);
        pManager->UpdateInterface();
        pManager->GetInterface()->SetBusy(false);
        pManager->GetInterface()->DrawGatesBars();
        pManager->SyncInterface();
    } while(dummy.first == -1 && dummy.second == -1);
    for(unsigned int i = 0; i < Gates.size(); i++)
        if(Gates[i] != NULL)
            if(Gates[i]->GetGraphicsInfo().Contains(pManager->GetInterface()->GetMousePosition(true)))
            {
                Act = Gates[i]->GetAction();
                break;
            }
    for(unsigned int i = 0; i < Buttons.size(); i++)
        if(Buttons[i] != NULL)
            if(Buttons[i]->GetAction() == ADD)
            {
                Buttons[i]->SetStatus(Button::NORMAL);
                break;
            }
    pManager->UpdateInterface();
    pManager->SyncInterface();
    pManager->ExecuteAction(Act);
}

void Add::Undo() {}

void Add::Redo() {}
