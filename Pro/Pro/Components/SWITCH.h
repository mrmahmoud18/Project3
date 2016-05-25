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
	void SwitchSignal();
	virtual void Reset();
	virtual bool IsConnected() const;
	virtual bool IsReady() const;
	virtual std::set<Component*> GetAssociatedComponents();
	virtual void ShiftBy(std::pair<int,int> Delta);
	virtual std::pair<int,int> GetCenter() const;
	virtual void GetIn(Grid* SimGrid);
	virtual void GetOut(Grid* SimGrid);
	virtual std::string GetLable();
	virtual void Operate();
	virtual void Draw(Interface* pInterface) const;
	virtual void Copy(ApplicationManager* pManager) const;

private:
    GraphicsInfo m_GfxInfo;
    std::string m_Label;
	OutputPin m_OutputPin;
	Signal m_Signal;
};

