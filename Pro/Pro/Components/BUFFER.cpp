#include "BUFFER.h"

#include "../GUI/Interface.h"

BUFFER::BUFFER(const GraphicsInfo & r_GfxInfo, std::string r_Label): Gate(r_GfxInfo, 5)
{
	m_InputPins.push_back(InputPin(std::pair<int,int> (r_GfxInfo.GetX()+2, r_GfxInfo.GetY()+6)));
	SetLabel(r_Label);
}



void BUFFER::Draw(Interface* pInterface)
{
	pInterface->DrawComponent(GetGraphicsInfo(), "BUFFER", GetStatus());
	for(unsigned int i = 0; i < m_InputPins.size(); i++)
        m_InputPins[i].Draw(pInterface);
    m_OutputPin.Draw(pInterface);
}
