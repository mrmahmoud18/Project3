#pragma once

#include "../GraphicsInfo.h"
#include "Component.h"
#include "OutputPin.h"

#include <string>

class SWITCH: public Component
{
public:
    SWITCH(const GraphicsInfo &r_GfxInfo, std::string r_Label="");
	const GraphicsInfo& GetGraphicsInfo() const;
	void SetLabel(std::string r_Label);
	OutputPin* GetOutputPin();
	virtual void Operate();
	virtual void Draw(Interface* pInterface);
	virtual bool IsValidToOperate();
	virtual bool IsValidToSimulate();
	virtual void ClearStatus();
private:
    GraphicsInfo m_GfxInfo;
    std::string m_Label;
	OutputPin m_OutputPin;
};

