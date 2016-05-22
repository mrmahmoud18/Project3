#include "NAND2.h"

#include "../ApplicationManager.h"
#include "../GUI/Interface.h"

NAND2::NAND2(const GraphicsInfo & r_GfxInfo, std::string r_Label) : Gate(r_GfxInfo, 5)
{
	m_InputPins.push_back(InputPin(std::pair<int, int>(r_GfxInfo.GetX() + 2, r_GfxInfo.GetY() + 5)));
	m_InputPins.push_back(InputPin(std::pair<int, int>(r_GfxInfo.GetX() + 2, r_GfxInfo.GetY() + 7)));
	SetLabel(r_Label);
}

void NAND2::Operate()
{

}

void NAND2::Draw(Interface* pInterface) const
{
	pInterface->DrawComponent(GetGraphicsInfo(), "NAND2", GetStatus());
	for(unsigned int i = 0; i < m_InputPins.size(); i++)
        m_InputPins[i].Draw(pInterface);
	m_OutputPin.Draw(pInterface);
}

void NAND2::Copy(ApplicationManager * pManager) const
{
	pManager->PushIntoClipboard(new NAND2(*this));
}
