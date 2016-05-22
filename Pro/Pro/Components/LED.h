#pragma once

#include "../GraphicsInfo.h"
#include "Component.h"
#include "InputPin.h"

#include <string>

class LED: public Component
{
public:
    LED(const GraphicsInfo &r_GfxInfo, std::string r_Label="");
	const GraphicsInfo& GetGraphicsInfo() const;
	void SetLabel(std::string r_Label);
	InputPin* GetInputPin();
	virtual void Operate();
	virtual void Draw(Interface* pInterface);
	virtual bool IsValidToOperate();
	virtual bool IsValidToSimulate();
	virtual void ClearStatus();
private:
    GraphicsInfo m_GfxInfo;
    std::string m_Label;
	InputPin m_InputPin;
};

