#pragma once

#include <utility>

class Connection;
class Interface;

class Pin
{
private:
    std::pair<int,int> m_Center;

public:
	enum Status { LOW, HIGH, FLOATING } m_Status;
	Pin(std::pair<int,int> r_Center);
	virtual ~Pin();
	void SetCenter(std::pair<int,int> r_Center);
	std::pair<int,int> GetCenter();
	void SetStatus(Status r_Status);
	Status GetStatus();
	virtual bool IsConnectable()=0;
	virtual void ConnectTo(Connection* r_Connection)=0;
	virtual void DeconnectFrom(Connection* r_Connection)=0;
	virtual void Draw(Interface* pInterface)=0;
	virtual bool IsValidToSimulate() = 0;
};
