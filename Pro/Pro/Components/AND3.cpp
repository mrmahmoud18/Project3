#include "AND3.h"

#include "../ApplicationManager.h"
#include "../GUI/Interface.h"

AND3::AND3(const GraphicsInfo & r_GfxInfo, std::string r_Label): Gate(r_GfxInfo, 5)
{
	m_InputPins.push_back(InputPin(std::pair<int, int>(r_GfxInfo.GetX() + 2, r_GfxInfo.GetY() + 5)));
	m_InputPins.push_back(InputPin(std::pair<int, int>(r_GfxInfo.GetX() + 2, r_GfxInfo.GetY() + 6)));
	m_InputPins.push_back(InputPin(std::pair<int, int>(r_GfxInfo.GetX() + 2, r_GfxInfo.GetY() + 7)));
	SetLabel(r_Label);
}

void AND3::Operate()
{

}

void AND3::Draw(Interface * pInterface) const
{
	pInterface->DrawComponent(GetGraphicsInfo(), "AND3", GetStatus());
	for (unsigned int i = 0; i < m_InputPins.size(); i++)
		m_InputPins[i].Draw(pInterface);
	m_OutputPin.Draw(pInterface);
}

void AND3::Copy(ApplicationManager* pManager) const
{
    pManager->PushIntoClipboard(new AND3(*this));
}
