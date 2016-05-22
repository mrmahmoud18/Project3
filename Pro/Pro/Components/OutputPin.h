#pragma once

#include "Pin.h"

#include <vector>

class Connection;

class OutputPin: public Pin
{
private:
	int m_FanOut;
	std::vector<Connection*> m_Connections;

public:
	OutputPin(std::pair<int,int> r_Center, int r_FanOut);
	virtual bool IsConnectable();
	virtual void ConnectTo(Connection* r_Connection);
	virtual void DeconnectFrom(Connection* r_Connection);
	virtual void Draw(Interface* pInterface);
	virtual bool IsValidToSimulate();
};
