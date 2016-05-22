#include "SWITCH.h"

#include "../Grid.h"
#include "../ApplicationManager.h"
#include "../GUI/Interface.h"

SWITCH::SWITCH(const GraphicsInfo &r_GfxInfo, std::string r_Label): m_GfxInfo(r_GfxInfo), m_OutputPin(std::pair<int,int> (r_GfxInfo.GetX()+10, r_GfxInfo.GetY()+6), 5)
{
    SetLabel(r_Label);
}

const GraphicsInfo& SWITCH::GetGraphicsInfo() const
{
    return m_GfxInfo;
}

void SWITCH::SetLabel(std::string r_Label)
{
    m_Label = r_Label;
}

OutputPin* SWITCH::GetOutputPin()
{
	return &m_OutputPin;
}

std::set<Component*> SWITCH::GetAssociatedComponents()
{
    std::vector<Connection*> dummy = m_OutputPin.GetConnections();
    std::set<Component*> AssociatedComponents;
    for(unsigned int i = 0; i < dummy.size(); i++)
        AssociatedComponents.insert((Component*)(dummy[i]));
    return AssociatedComponents;
}

void SWITCH::ShiftBy(std::pair<int,int> Delta)
{
    m_GfxInfo.ShiftBy(Delta);
}

std::pair<int,int> SWITCH::GetCenter() const
{
    return m_GfxInfo.GetCenter();
}

void SWITCH::GetIn(Grid* SimGrid)
{
    SimGrid->AddSWITCH(this);
}

void SWITCH::GetOut(Grid* SimGrid)
{
    SimGrid->RemoveSWITCH(this);
}

void SWITCH::Operate()
{
    ///TODO
}

void SWITCH::Draw(Interface* pInterface) const
{
    pInterface->DrawComponent(m_GfxInfo, "SWITCH", GetStatus());
    m_OutputPin.Draw(pInterface);
}

void SWITCH::Copy(ApplicationManager* pManager) const
{
    pManager->PushIntoClipboard(new SWITCH(*this));
}
