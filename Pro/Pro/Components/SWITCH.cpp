#include "SWITCH.h"

#include "../Grid.h"
#include "../ApplicationManager.h"
#include "../GUI/Interface.h"

SWITCH::SWITCH(const GraphicsInfo &r_GfxInfo, std::string r_Label): m_GfxInfo(r_GfxInfo), m_OutputPin(std::pair<int,int> (r_GfxInfo.GetX()+10, r_GfxInfo.GetY()+6), 5)
{
    SetLabel(r_Label);
    m_Signal = LOW;
}

const GraphicsInfo& SWITCH::GetGraphicsInfo() const
{
    return m_GfxInfo;
}

void SWITCH::SetLabel(std::string r_Label)
{
    m_Label = r_Label;
}

void SWITCH::SetSignal(Signal r_signal)
{
	m_Signal = r_signal;
}

OutputPin* SWITCH::GetOutputPin()
{
	return &m_OutputPin;
}

void SWITCH::SwitchSignal()
{
    if(m_Signal == LOW)
    {
        m_Signal = HIGH;
        SetStatus(ON);
    }
    else
    {
        m_Signal = LOW;
        SetStatus(NORMAL);
    }
}

void SWITCH::Reset()
{
    SetStatus(NORMAL);
    m_OutputPin.SetStatus(FLOATING);
}

bool SWITCH::IsConnected() const
{
    return m_OutputPin.IsConnected();
}

bool SWITCH::IsReady() const
{
    return true;
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
    m_OutputPin.ShiftBy(Delta);
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

std::string SWITCH::GetLable()
{
	return m_Label;
}

void SWITCH::Operate()
{
    SetStatus((m_Signal == HIGH) ? ON : NORMAL);
    m_OutputPin.SetStatus(m_Signal);
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
