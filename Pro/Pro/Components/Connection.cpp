#include "Connection.h"

#include "../ApplicationManager.h"
#include "../Grid.h"
#include "Pin.h"
#include "../GUI/Interface.h"

Connection::Connection(Pin* r_InputPin, Pin* r_OutputPin, const std::vector< std::pair<int,int> >& r_Vertices)
{
    m_InputPin = r_InputPin;
    m_OutputPin = r_OutputPin;
    m_Vertices = r_Vertices;
}

void Connection::Update(const std::vector< std::pair<int,int> >& r_Vertices)
{
    m_Vertices = r_Vertices;
}

const std::vector< std::pair<int,int> >& Connection::GetPath()
{
    return m_Vertices;
}

std::set<Component*> Connection::GetAssociatedComponents()
{
    std::set<Component*> dummy;
    return dummy;
}

void Connection::ShiftBy(std::pair<int,int> Delta)
{
    for(unsigned int i = 0; i < m_Vertices.size(); i++)
    {
        m_Vertices[i].first += Delta.first;
        m_Vertices[i].second += Delta.second;
    }
}

std::pair<int,int> Connection::GetCenter() const
{
    return std::pair<int,int> ((m_Vertices.front().first+m_Vertices.back().first)/2, (m_Vertices.front().second+m_Vertices.back().second)/2);
}

void Connection::GetIn(Grid* SimGrid)
{
    SimGrid->AddConnection(this);
    m_InputPin->ConnectTo(this);
    m_OutputPin->ConnectTo(this);
}

void Connection::GetOut(Grid* SimGrid)
{
    SimGrid->RemoveConnection(this);
    m_InputPin->DeconnectFrom(this);
    m_OutputPin->DeconnectFrom(this);
}

void Connection::Operate()
{
    m_OutputPin->SetStatus(m_InputPin->GetStatus());
}

void Connection::Draw(Interface* pInterface) const
{
    pInterface->DrawConnection(m_Vertices, GetStatus(), m_InputPin->GetStatus());
    m_InputPin->Draw(pInterface);
    m_OutputPin->Draw(pInterface);
}

void Connection::Copy(ApplicationManager* pManager) const
{
    return;
}
