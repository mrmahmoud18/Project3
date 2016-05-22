#include "AddComponent.h"

#include "../ApplicationManager.h"
#include "../Components/AND2.h"

AddComponent::AddComponent(ApplicationManager *pApp, Action::ActionType r_ActionType): Action(pApp)
{
	m_ActionType = r_ActionType;
}

void AddComponent::ReadActionParameters()
{
	std::string FilePath;
	Center = std::pair<int, int>(-1, -1);
	switch (m_ActionType)
	{
	case ADD_BUFF:
	    FilePath = "BUFFER";
		break;
	case ADD_INV:
		FilePath = "NOT";
		break;
	case ADD_AND_GATE_2:
		FilePath = "AND2";
		break;
	case ADD_NAND_GATE_2:
		FilePath = "NAND2";
		break;
	case ADD_OR_GATE_2:
		FilePath = "OR2";
		break;
	case ADD_NOR_GATE_2:
		FilePath = "NOR2";
		break;
	case ADD_XOR_GATE_2:
		FilePath = "XOR2";
		break;
	case ADD_XNOR_GATE_2:
		FilePath = "XNOR2";
		break;
	case ADD_AND_GATE_3:
		FilePath = "AND3";
		break;
	case ADD_NAND_GATE_3:
		FilePath = "NAND3";
		break;
	case ADD_OR_GATE_3:
		FilePath = "OR3";
		break;
	case ADD_NOR_GATE_3:
		FilePath = "NOR3";
		break;
	case ADD_XOR_GATE_3:
		FilePath = "XOR3";
		break;
	case ADD_XNOR_GATE_3:
		FilePath = "XNOR3";
		break;
	case ADD_SWITCH:
		FilePath = "SWITCH";
		break;
	case ADD_LED:
		FilePath = "LED";
		break;
	default:
		return;
	}
	pManager->GetInterface()->SetBusy(true);
	do
	{
		std::pair<int,int> Position = pManager->GetInterface()->GetMousePosition();
		Center = pManager->GetInterface()->GetInstantClick();
		pManager->UpdateInterface();
		if(pManager->GetGrid()->IsValidCenter(Position))
            pManager->GetInterface()->DrawComponent(GraphicsInfo(Position.first-6, Position.second-6, 12, 12), FilePath, Component::NORMAL);
		else
            pManager->GetInterface()->DrawComponent(GraphicsInfo(Position.first-6, Position.second-6, 12, 12), FilePath, Component::INVALID);
        pManager->GetInterface()->ResetWindow();
        pManager->GetInterface()->SetMouseStatus(Interface::HIDDEN);
        pManager->SyncInterface();
	} while (Center == std::pair<int, int>(-1, -1));
	pManager->GetInterface()->SetBusy(false);
	pManager->GetInterface()->SetMouseStatus(Interface::POINTER);
}

void AddComponent::Execute()
{
	ReadActionParameters();
	if ((Center == std::pair<int, int>(-1, -1)) || !(pManager->GetGrid()->IsValidCenter(Center)))
		return;
	switch (m_ActionType)
	{
	case ADD_BUFF:
		break;
	case ADD_INV:
		break;
	case ADD_AND_GATE_2:
		pComp  = new AND2((GraphicsInfo(Center.first - 6, Center.second - 6, 12, 12)));
		break;
	case ADD_NAND_GATE_2:
		break;
	case ADD_OR_GATE_2:
		break;
	case ADD_NOR_GATE_2:
		break;
	case ADD_XOR_GATE_2:
		break;
	case ADD_XNOR_GATE_2:
		break;
	case ADD_AND_GATE_3:
		break;
	case ADD_NAND_GATE_3:
		break;
	case ADD_OR_GATE_3:
		break;
	case ADD_NOR_GATE_3:
		break;
	case ADD_XOR_GATE_3:
		break;
	case ADD_XNOR_GATE_3:
		break;
	case ADD_SWITCH:
		break;
	case ADD_LED:
		break;
	default:
		break;
	}
	pManager->GetComponents().push_back(pComp);
	//pManager->GetGrid()->AddComponent(Center, pComp);
}

void AddComponent::Undo()
{
	pManager->GetComponents().pop_back();
	pManager->GetGrid()->DeleteComponent(Center);
}

void AddComponent::Redo()
{
	pManager->GetComponents().push_back(pComp);
	//pManager->GetGrid()->AddComponent(Center, pComp);
}
