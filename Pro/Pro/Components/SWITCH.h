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
	virtual std::set<Component*> GetAssociatedComponents();
	virtual void ShiftBy(std::pair<int,int> Delta);
	virtual std::pair<int,int> GetCenter() const;
	virtual void GetIn(Grid* SimGrid);
	virtual void GetOut(Grid* SimGrid);
	virtual void Operate();
	virtual void Draw(Interface* pInterface) const;
	virtual void Copy(ApplicationManager* pManager) const;

private:
    GraphicsInfo m_GfxInfo;
    std::string m_Label;
	OutputPin m_OutputPin;
};

