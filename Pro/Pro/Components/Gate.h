#pragma once

#include "../GraphicsInfo.h"
#include "Component.h"
#include "InputPin.h"
#include "OutputPin.h"

#include <string>
#include <vector>

class Gate: public Component
{
private:
    GraphicsInfo m_GfxInfo;
    std::string m_Label;

protected:
	std::vector<InputPin> m_InputPins;
	OutputPin m_OutputPin;

public:
	Gate(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	const GraphicsInfo& GetGraphicsInfo() const;
	void SetLabel(std::string r_Label);
    std::vector<InputPin>& GetInputPins();
	OutputPin* GetOutputPin();
	virtual bool IsValidToOperate();
	virtual bool IsValidToSimulate();
	virtual void ClearStatus();
};
