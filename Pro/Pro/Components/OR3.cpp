#include "OR3.h"

#include "../GUI/Interface.h"

OR3::OR3(const GraphicsInfo & r_GfxInfo, std::string r_Label) : Gate(r_GfxInfo, 5)
{
	m_InputPins.push_back(InputPin(std::pair<int, int>(r_GfxInfo.GetX() + 2, r_GfxInfo.GetY() + 5)));
	m_InputPins.push_back(InputPin(std::pair<int, int>(r_GfxInfo.GetX() + 2, r_GfxInfo.GetY() + 6)));
	m_InputPins.push_back(InputPin(std::pair<int, int>(r_GfxInfo.GetX() + 2, r_GfxInfo.GetY() + 7)));
	SetLabel(r_Label);
}

void OR3::Operate()
{
	for (unsigned int i = 0; i < m_InputPins.size(); i++)
	{
		if (m_InputPins[i].GetStatus() == Pin::LOW)
		{
			m_OutputPin.SetStatus(Pin::LOW);
		}
	}
	m_OutputPin.SetStatus(Pin::HIGH);
}

void OR3::Draw(Interface * pInterface)
{
	pInterface->DrawComponent(GetGraphicsInfo(), "OR3", GetStatus());
	for (unsigned int i = 0; i < m_InputPins.size(); i++)
		m_InputPins[i].Draw(pInterface);
	m_OutputPin.Draw(pInterface);
}

