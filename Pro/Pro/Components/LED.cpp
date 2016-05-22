#include "LED.h"

#include "../Grid.h"
#include "../ApplicationManager.h"
#include "../GUI/Interface.h"

LED::LED(const GraphicsInfo &r_GfxInfo, std::string r_Label): m_GfxInfo(r_GfxInfo), m_InputPin(std::pair<int,int> (r_GfxInfo.GetX()+2, r_GfxInfo.GetY()+6))
{
    SetLabel(r_Label);
}

const GraphicsInfo& LED::GetGraphicsInfo() const
{
    return m_GfxInfo;
}

void LED::SetLabel(std::string r_Label)
{
    m_Label = r_Label;
}

InputPin* LED::GetInputPin()
{
	return &m_InputPin;
}

std::set<Component*> LED::GetAssociatedComponents()
{
    std::set<Component*> AssociatedComponents;
    AssociatedComponents.insert((Component*)m_InputPin.GetConnection());
    return AssociatedComponents;
}

void LED::ShiftBy(std::pair<int,int> Delta)
{
    m_GfxInfo.ShiftBy(Delta);
}

std::pair<int,int> LED::GetCenter() const
{
    return m_GfxInfo.GetCenter();
}

void LED::GetIn(Grid* SimGrid)
{
    SimGrid->AddLED(this);
}

void LED::GetOut(Grid* SimGrid)
{
    SimGrid->RemoveLED(this);
}

void LED::Operate()
{
    ///TODO
}

void LED::Draw(Interface* pInterface) const
{
    pInterface->DrawComponent(m_GfxInfo, "LED", GetStatus());
    m_InputPin.Draw(pInterface);
}

void LED::Copy(ApplicationManager* pManager) const
{
    pManager->PushIntoClipboard(new LED(*this));
}
