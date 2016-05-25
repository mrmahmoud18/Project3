#include "NOT.h"

#include "../ApplicationManager.h"
#include "../GUI/Interface.h"

NOT::NOT(const GraphicsInfo & r_GfxInfo, std::string r_Label): Gate(r_GfxInfo, 5)
{
	m_InputPins.push_back(InputPin(std::pair<int,int> (r_GfxInfo.GetX()+2, r_GfxInfo.GetY()+6)));
	SetLabel(r_Label);
}

void NOT::Operate()
{
	if (m_InputPins[0].GetStatus() == Signal::HIGH)
		m_OutputPin.SetStatus(Signal::LOW);
	else
		m_OutputPin.SetStatus(Signal::HIGH);
}

void NOT::Draw(Interface* pInterface) const
{
	pInterface->DrawComponent(GetGraphicsInfo(), "NOT", GetStatus());
	for(unsigned int i = 0; i < m_InputPins.size(); i++)
        m_InputPins[i].Draw(pInterface);
    m_OutputPin.Draw(pInterface);
}

void NOT::Copy(ApplicationManager * pManager) const
{
	pManager->PushIntoClipboard(new NOT(*this));
}
