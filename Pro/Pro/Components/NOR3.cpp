#include "NOR3.h"

#include "../GUI/Interface.h"

NOR3::NOR3(const GraphicsInfo & r_GfxInfo, std::string r_Label) : Gate(r_GfxInfo, 5)
{
	m_InputPins.push_back(InputPin(std::pair<int, int>(r_GfxInfo.GetX() + 2, r_GfxInfo.GetY() + 5)));
	m_InputPins.push_back(InputPin(std::pair<int, int>(r_GfxInfo.GetX() + 2, r_GfxInfo.GetY() + 6)));
	m_InputPins.push_back(InputPin(std::pair<int, int>(r_GfxInfo.GetX() + 2, r_GfxInfo.GetY() + 7)));
	SetLabel(r_Label);
}

void NOR3::Operate()
{
	for (unsigned int i = 0; i < m_InputPins.size(); i++)
	{
		if (m_InputPins[i].GetStatus() == Pin::HIGH)
		{
			m_OutputPin.SetStatus(Pin::LOW);
		}
	}
	m_OutputPin.SetStatus(Pin::HIGH);
}

void NOR3::Draw(Interface * pInterface)
{
	pInterface->DrawComponent(GetGraphicsInfo(), "NOR3", GetStatus());
	for (unsigned int i = 0; i < m_InputPins.size(); i++)
		m_InputPins[i].Draw(pInterface);
	m_OutputPin.Draw(pInterface);
}

