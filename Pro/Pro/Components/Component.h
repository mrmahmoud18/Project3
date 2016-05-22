#pragma once

class Interface;

class Component
{
public:
    enum Status{NORMAL, SELECTED, INVALID};
	Component();
	virtual ~Component();
	void SetStatus(Status r_Status);
	Status GetStatus();
	virtual void Operate()=0;
	virtual void Draw(Interface* pInterface)=0;
	virtual bool IsValidToOperate()=0;
	virtual bool IsValidToSimulate() = 0;
	virtual void ClearStatus() = 0;
private:
	Status m_Status;
};
