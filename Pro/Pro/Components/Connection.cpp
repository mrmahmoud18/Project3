#include "Connection.h"

#include "Pin.h"
#include "../GUI/Interface.h"

Connection::Connection(Pin* r_InputPin, Pin* r_OutputPin, const std::vector< std::pair<int,int> >& r_Path)
{
    m_InputPin = r_InputPin;
    m_OutputPin =r_OutputPin;
    m_Path = r_Path;
}

void Connection::Update(const std::vector< std::pair<int,int> >& r_Vertices)
{
    m_Path = r_Vertices;
}

void Connection::Operate()
{
    m_OutputPin->SetStatus(m_InputPin->GetStatus());
}

void Connection::Draw(Interface* pInterface)
{
    pInterface->DrawConnection(m_Path, GetStatus());
    m_InputPin->Draw(pInterface);
    m_OutputPin->Draw(pInterface);
}

bool Connection::IsValidToOperate()
{
	return (m_InputPin->GetStatus() != Pin::FLOATING);
}

bool Connection::IsValidToSimulate()
{
	return true;
}

void Connection::ClearStatus()
{
	m_InputPin->SetStatus(Pin::FLOATING);
	m_OutputPin->SetStatus(Pin::FLOATING);
}

std::vector<std::pair<int, int>> Connection::GetPath()
{
	return m_Path;
}

Pin * Connection::GetInputPin()
{
	return m_InputPin ;
}

Pin * Connection::GetOutPin()
{
	return m_OutputPin;
}
