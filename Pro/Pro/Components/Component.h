#pragma once

#include <set>
#include <fstream>

#include "../Enums.h"

class ApplicationManager;
class Grid;
class Interface;

class Component
{
public:
	Component();
	virtual ~Component();
	void SetStatus(ComponentStatus r_Status);
	ComponentStatus GetStatus() const;
	virtual std::set<Component*> GetAssociatedComponents()=0;
	virtual void ShiftBy(std::pair<int,int> Delta)=0;
	virtual std::pair<int,int> GetCenter() const=0;
	virtual void GetIn(Grid* SimGrid)=0;
	virtual void GetOut(Grid* SimGrid)=0;
	virtual void Operate()=0;
	virtual void Draw(Interface* pInterface) const=0;
	virtual void Copy(ApplicationManager* pManager) const=0;
	//virtual void Save(std::ofstream& File)=0;

private:
	ComponentStatus m_Status;
};
