#include "Gate.h"

#include "InputPin.h"

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

bool Gate::IsValidToOperate()
{
	for (unsigned int i = 0; i < m_InputPins.size(); i++)
	{
		if (m_InputPins[i].GetStatus() == Pin::FLOATING)
		{
			return false;
		}
	}
	return true;
}

bool Gate::IsValidToSimulate()
{
	if (! m_OutputPin.IsValidToSimulate())
	{
		return false;
	}
	for (unsigned int i = 0; i < m_InputPins.size(); i++)
	{
		if (!m_InputPins[i].IsValidToSimulate())return false;
	}
	return true;
}

void Gate::ClearStatus()
{
	m_OutputPin.SetStatus(Pin::FLOATING);
	for (unsigned int i = 0; i < m_InputPins.size(); i++)
	{
		m_InputPins[i].SetStatus(Pin::FLOATING);
	}
}
