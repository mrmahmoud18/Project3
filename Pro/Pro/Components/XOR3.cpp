#include "XOR3.h"

#include "../GUI/Interface.h"

XOR3::XOR3(const GraphicsInfo & r_GfxInfo, std::string r_Label) : Gate(r_GfxInfo, 5)
{
	m_InputPins.push_back(InputPin(std::pair<int, int>(r_GfxInfo.GetX() + 2, r_GfxInfo.GetY() + 5)));
	m_InputPins.push_back(InputPin(std::pair<int, int>(r_GfxInfo.GetX() + 2, r_GfxInfo.GetY() + 6)));
	m_InputPins.push_back(InputPin(std::pair<int, int>(r_GfxInfo.GetX() + 2, r_GfxInfo.GetY() + 7)));
	SetLabel(r_Label);
}

void XOR3::Operate()
{
	int cont = 0;
	for (unsigned int i = 0; i < m_InputPins.size(); i++)
	{
		if (m_InputPins[i].GetStatus() == Pin::HIGH)
		{
			cont++;
		}
	}
	if (cont == 1 || cont == 3)
	{
		m_OutputPin.SetStatus(Pin::HIGH);
	}
	else
	{
		m_OutputPin.SetStatus(Pin::LOW);
	}
}

void XOR3::Draw(Interface * pInterface)
{
	pInterface->DrawComponent(GetGraphicsInfo(), "XOR3", GetStatus());
	for (unsigned int i = 0; i < m_InputPins.size(); i++)
		m_InputPins[i].Draw(pInterface);
	m_OutputPin.Draw(pInterface);
}

