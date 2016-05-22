#include "NAND3.h"

#include "../GUI/Interface.h"

NAND3::NAND3(const GraphicsInfo & r_GfxInfo, std::string r_Label) : Gate(r_GfxInfo, 5)
{
	m_InputPins.push_back(InputPin(std::pair<int, int>(r_GfxInfo.GetX() + 2, r_GfxInfo.GetY() + 5)));
	m_InputPins.push_back(InputPin(std::pair<int, int>(r_GfxInfo.GetX() + 2, r_GfxInfo.GetY() + 6)));
	m_InputPins.push_back(InputPin(std::pair<int, int>(r_GfxInfo.GetX() + 2, r_GfxInfo.GetY() + 7)));
	SetLabel(r_Label);
}

void NAND3::Operate()
{
	for (unsigned int i = 0; i < m_InputPins.size(); i++)
	{
		if (m_InputPins[i].GetStatus() == Pin::LOW)
		{
			m_OutputPin.SetStatus(Pin::HIGH);
			return;
		}
	}
	m_OutputPin.SetStatus(Pin::LOW);
}

void NAND3::Draw(Interface * pInterface)
{
	pInterface->DrawComponent(GetGraphicsInfo(), "NAND3", GetStatus());
	for (unsigned int i = 0; i < m_InputPins.size(); i++)
		m_InputPins[i].Draw(pInterface);
	m_OutputPin.Draw(pInterface);
}

