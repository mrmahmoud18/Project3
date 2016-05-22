#include "LED.h"

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

void LED::Operate()
{
    ///TODO
}

void LED::Draw(Interface* pInterface)
{
    pInterface->DrawComponent(m_GfxInfo, "LED", GetStatus());
    m_InputPin.Draw(pInterface);
}

bool LED::IsValidToOperate()
{
	return (m_InputPin.GetStatus() != Pin::FLOATING);
}

bool LED::IsValidToSimulate()
{
	return m_InputPin.IsValidToSimulate();
}

void LED::ClearStatus()
{
	m_InputPin.SetStatus(Pin::FLOATING);
}
