#pragma once

#include "Pin.h"

class Connection;

class InputPin: public Pin
{
private:
	Connection* m_Connection;

public:
	InputPin(std::pair<int,int> r_Center);
	Connection* GetConnection();
	virtual bool IsConnectable() const;
	virtual void ConnectTo(Connection* r_Connection);
	virtual void DeconnectFrom(Connection* r_Connection);
	virtual void Draw(Interface* pInterface) const;
};
