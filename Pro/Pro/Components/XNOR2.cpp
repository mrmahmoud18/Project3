#include "XNOR2.h"

#include "../GUI/Interface.h"

XNOR2::XNOR2(const GraphicsInfo & r_GfxInfo, std::string r_Label) : Gate(r_GfxInfo, 5)
{
	m_InputPins.push_back(InputPin(std::pair<int, int>(r_GfxInfo.GetX() + 2, r_GfxInfo.GetY() + 5)));
	m_InputPins.push_back(InputPin(std::pair<int, int>(r_GfxInfo.GetX() + 2, r_GfxInfo.GetY() + 7)));
	SetLabel(r_Label);
}

void XNOR2::Operate()
{
	int cont = 0;
	for (unsigned int  i = 0; i < m_InputPins.size(); i++)
	{
		if (m_InputPins[i].GetStatus() == Pin::HIGH)
		{
			cont++;
		}
	}
	if (cont==2 || cont==0)
	{
		m_OutputPin.SetStatus(Pin::HIGH);
	}
	else
	{
		m_OutputPin.SetStatus(Pin::LOW);
	}
}

void XNOR2::Draw(Interface* pInterface)
{
	pInterface->DrawComponent(GetGraphicsInfo(), "XNOR2", GetStatus());
	for(unsigned int i = 0; i < m_InputPins.size(); i++)
        m_InputPins[i].Draw(pInterface);
	m_OutputPin.Draw(pInterface);
}



