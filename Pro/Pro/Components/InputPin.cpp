#include "InputPin.h"

#include "../GUI/Interface.h"

InputPin::InputPin(std::pair<int,int> r_Center): Pin(r_Center)
{
    m_Connection = NULL;
}

Connection* InputPin::GetConnection()
{
    return m_Connection;
}

bool InputPin::IsConnectable() const
{
    return m_Connection == NULL;
}

void InputPin::ConnectTo(Connection * r_Connection)
{
	m_Connection = r_Connection;
}

void InputPin::DeconnectFrom(Connection* r_Connection)
{
    if(m_Connection == r_Connection)
        m_Connection = NULL;
    else
        throw;
}

void InputPin::Draw(Interface* pInterface) const
{
    pInterface->DrawPin(GetCenter(), m_Connection != NULL);
}
