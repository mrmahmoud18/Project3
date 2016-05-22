#include "OutputPin.h"

#include "../GUI/Interface.h"

OutputPin::OutputPin(std::pair<int,int> r_Center, int r_FanOut): Pin(r_Center)
{
	m_FanOut = r_FanOut;
}

bool OutputPin::IsConnectable()
{
    return m_Connections.size() == 0;
}

void OutputPin::ConnectTo(Connection * r_Connection)
{
	m_Connections.push_back(r_Connection);
}

void OutputPin::DeconnectFrom(Connection * r_Connection)
{
	///NOT GOOD
	m_Connections.erase(std::find(m_Connections.begin(), m_Connections.end(), r_Connection));
}

void OutputPin::Draw(Interface* pInterface)
{
    pInterface->DrawPin(GetCenter(), m_Connections.size() != 0);
}

bool OutputPin::IsValidToSimulate()
{
	return (m_Connections.size() != 0);
}
