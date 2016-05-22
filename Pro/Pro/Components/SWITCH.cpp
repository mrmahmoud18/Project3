#include "SWITCH.h"

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

void SWITCH::Operate()
{
    ///TODO
}

void SWITCH::Draw(Interface* pInterface)
{
    pInterface->DrawComponent(m_GfxInfo, "SWITCH", GetStatus());
    m_OutputPin.Draw(pInterface);
}

bool SWITCH::IsValidToOperate()
{
	return true;
}

bool SWITCH::IsValidToSimulate()
{
	return m_OutputPin.IsValidToSimulate() ;
}

void SWITCH::ClearStatus()
{
	m_OutputPin.SetStatus(Pin::FLOATING);
}
