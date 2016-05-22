#include "OutputPin.h"

#include "../GUI/Interface.h"

OutputPin::OutputPin(std::pair<int,int> r_Center, int r_FanOut): Pin(r_Center)
{
	m_FanOut = r_FanOut;
}

std::vector<Connection*> OutputPin::GetConnections()
{
    return m_Connections;
}

bool OutputPin::IsConnectable() const
{
    return m_Connections.size() == 0;
}

void OutputPin::ConnectTo(Connection * r_Connection)
{
	m_Connections.push_back(r_Connection);
}

void OutputPin::DeconnectFrom(Connection * r_Connection)
{
	std::vector<Connection*>::iterator dummyIt = std::find(m_Connections.begin(), m_Connections.end(), r_Connection);
    if(dummyIt == m_Connections.end())
        throw;
    m_Connections.erase(dummyIt);
}

void OutputPin::Draw(Interface* pInterface) const
{
    pInterface->DrawPin(GetCenter(), m_Connections.size() != 0);
}
