#include "AND2.h"

#include "../ApplicationManager.h"
#include "../GUI/Interface.h"

AND2::AND2(const GraphicsInfo & r_GfxInfo, std::string r_Label): Gate(r_GfxInfo, 5)
{
	m_InputPins.push_back(InputPin(std::pair<int,int> (r_GfxInfo.GetX()+2, r_GfxInfo.GetY()+5)));
	m_InputPins.push_back(InputPin(std::pair<int,int> (r_GfxInfo.GetX()+2, r_GfxInfo.GetY()+7)));
	SetLabel(r_Label);
}

void AND2::Operate()
{
    ///TODO
}

void AND2::Draw(Interface* pInterface) const
{
	pInterface->DrawComponent(GetGraphicsInfo(), "AND2", GetStatus());
	for(unsigned int i = 0; i < m_InputPins.size(); i++)
        m_InputPins[i].Draw(pInterface);
    m_OutputPin.Draw(pInterface);
}

void AND2::Copy(ApplicationManager* pManager) const
{
    pManager->PushIntoClipboard(new AND2(*this));
}
