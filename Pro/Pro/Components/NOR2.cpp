#include "NOR2.h"

#include "../ApplicationManager.h"
#include "../GUI/Interface.h"

NOR2::NOR2(const GraphicsInfo & r_GfxInfo, std::string r_Label) : Gate(r_GfxInfo, 5)
{
	m_InputPins.push_back(InputPin(std::pair<int, int>(r_GfxInfo.GetX() + 2, r_GfxInfo.GetY() + 5)));
	m_InputPins.push_back(InputPin(std::pair<int, int>(r_GfxInfo.GetX() + 2, r_GfxInfo.GetY() + 7)));
	SetLabel(r_Label);
}

void NOR2::Operate()
{

}

void NOR2::Draw(Interface* pInterface) const
{
	pInterface->DrawComponent(GetGraphicsInfo(), "NOR2", GetStatus());
	for(unsigned int i = 0; i < m_InputPins.size(); i++)
        m_InputPins[i].Draw(pInterface);
	m_OutputPin.Draw(pInterface);
}

void NOR2::Copy(ApplicationManager * pManager) const
{
	pManager->PushIntoClipboard(new NOR2(*this));
}
