#include "Gate.h"

#include "InputPin.h"
#include "../Grid.h"

Gate::Gate(const GraphicsInfo &r_GfxInfo, int r_FanOut): m_GfxInfo(r_GfxInfo), m_OutputPin(std::pair<int,int> (r_GfxInfo.GetX()+10, r_GfxInfo.GetY()+6), r_FanOut) {}

const GraphicsInfo& Gate::GetGraphicsInfo() const
{
    return m_GfxInfo;
}

void Gate::SetLabel(std::string r_Label)
{
    m_Label = r_Label;
}

std::vector<InputPin>& Gate::GetInputPins()
{
    return m_InputPins;
}

OutputPin* Gate::GetOutputPin()
{
    return &m_OutputPin;
}

std::set<Component*> Gate::GetAssociatedComponents()
{
    std::vector<Connection*> dummy = m_OutputPin.GetConnections();
    std::set<Component*> AssociatedComponents;
    for(unsigned int i = 0; i < dummy.size(); i++)
        AssociatedComponents.insert((Component*)(dummy[i]));
    for(unsigned int i = 0; i < m_InputPins.size(); i++)
        AssociatedComponents.insert((Component*)(m_InputPins[i].GetConnection()));
    return AssociatedComponents;
}

void Gate::ShiftBy(std::pair<int,int> Delta)
{
    m_GfxInfo.ShiftBy(Delta);
}

std::pair<int,int> Gate::GetCenter() const
{
    return m_GfxInfo.GetCenter();
}

void Gate::GetIn(Grid* SimGrid)
{
    SimGrid->AddGate(this);
}

void Gate::GetOut(Grid* SimGrid)
{
    SimGrid->RemoveGate(this);
}
