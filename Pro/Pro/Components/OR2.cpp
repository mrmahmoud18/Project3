#include "OR2.h"

#include "../ApplicationManager.h"
#include "../GUI/Interface.h"

OR2::OR2(const GraphicsInfo & r_GfxInfo, std::string r_Label) : Gate(r_GfxInfo, 5)
{
	m_InputPins.push_back(InputPin(std::pair<int, int>(r_GfxInfo.GetX() + 2, r_GfxInfo.GetY() + 5)));
	m_InputPins.push_back(InputPin(std::pair<int, int>(r_GfxInfo.GetX() + 2, r_GfxInfo.GetY() + 7)));
	SetLabel(r_Label);
}

void OR2::Operate()
{

}

void OR2::Draw(Interface* pInterface) const
{
	pInterface->DrawComponent(GetGraphicsInfo(), "OR2", GetStatus());
	for(unsigned int i = 0; i < m_InputPins.size(); i++)
        m_InputPins[i].Draw(pInterface);
	m_OutputPin.Draw(pInterface);
}

void OR2::Copy(ApplicationManager * pManager) const
{
	pManager->PushIntoClipboard(new OR2(*this));
}
